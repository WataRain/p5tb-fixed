/***************************************************************
I am thou, and thou art I.
Thou has acquired a new vowr
It shall become the wings of rebellion
that breaketh thy chains of captivity.
With the birth of the CCPROG1 Persona,
I have obtained the winds of blessing
that shall lead to freedom and new power.
I pledge that this power will result in my own work, based on my personal
efforts in studying and applying the concepts learned.
I have constructed the functions and their respective algorithms and
corresponding code by myself, formed from my own bonds.
The program was run, tested, and debugged by my own efforts.
I further certify that I have not copied in part or whole or otherwise
plagiarized the work of other students, persons, and/or personas.
The bond with this CCPROG1 persona is my own.
Justin Rainier A. Go, DLSU ID# 12306851
****************************************************************/

/*
Description:
Although I already had my MP Demo last December 7, 2023 with Version 5, there
were some small quirks in my code at the time. This version hopes to fix those
bugs to provide a once-and-for-all "safe" version of the program, without any
undefined behavior. Particularly, I am concerned with the following quirks:
1. [/] The "Saturady" typo
2. [/] Gifting confidants should make them unavailable for the rest of the day
3. [/] Hanging out with confidants should have a chance to boost a random stat
4. [/] Using strcat() instead of sprintf() to concatenate strings
5. [/] Remove extra format string in the default case of the conf. flavor text
6. [/] Smaller CHAR_LIMIT for items to prevent possible string overflow

Programmed by: Justin Rainier Go S20B
https://watarain.github.io/records-of-rain/index.html

Version: 6

Acknowledgements:
https://tforgione.fr/posts/ansi-escape-codes/
https://gist.github.com/RabaDabaDoba/145049536f815903c79944599c6f952a
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>

#include "mp_definitions.c"
#include "mp_events.c"
#include "mp_events2.c"
#include "mp_functions.c"
#include "mp_saving.c"
#include "mp_ui.c"
#include "mp_game_actions.c"
#include "mp_handlers.c"

int main()
{
    /* ------------------------ Var declarations ------------------------ */

    // Player details -- will be saved and loaded

    // Confidant points
    int aConfPts[AMOUNT_CONFIDANTS];
    set(aConfPts, AMOUNT_CONFIDANTS, LOCKED);

    // Social stat points
    int aStatPts[AMOUNT_STATS];
    set(aStatPts, AMOUNT_STATS, 0);

    // Player inventory
    int aItems[ITEM_MENU_LIMIT];
    set(aItems, ITEM_MENU_LIMIT, NONE);

    // Possible actions @ nLocation
    int aActions[ACTION_MENU_LIMIT];
    set(aActions, ACTION_MENU_LIMIT, NONE);

    // aConfGifted[SOJIRO] == true if we have gifted SOJIRO in this playthrough
    int aConfGifted[AMOUNT_CONFIDANTS];
    set(aConfGifted, AMOUNT_CONFIDANTS, false);

    // The above, but resets each day
    int aConfGiftedToday[AMOUNT_CONFIDANTS];
    set(aConfGifted, AMOUNT_CONFIDANTS, false);


    /* A bool array where each index corresponds to an item
    (Element is true if the player did purchase that item today,
    otherwise it is false) */
    int aItemsBoughtToday[AMOUNT_ITEMS];
    set(aItemsBoughtToday, AMOUNT_ITEMS, false);

    int nLocation;
    int nYen = 0;
    int nBBBLv = 1;
    int nDay = 1;
    int nStartPeriod = AFTERNOON;
    int nPeriod;

    // Flags
    int bQuit = false;
    int bTimePassed;
    int bLocationChange;
    int bSaveFileLoaded = false;
    int bDoRefresh = false;
    int bResetFooter = false;
    int bStatViewToggle = true;
    int bLentMoney = false;
    int bGiftedConfidant = false;

    // UI
    char aTitleOptions[2][CHR_LIMIT] = {"New Game", "Load Game"};
    int nOldLocation;  // Player's position before moving somewhere new
    int nHighlight;    // Position of current selection in the menu
    int nSelection;    // ID of selected action or item
    int nInput;        // "Input events", e.g. MENU_UP, MAP_NORTH, CONFIRM

    // File IO
    FILE *pFile;
    int nSaveNum;

    // Miscellaneous
    int nItem;         // Used to reset aItemsBoughtToday at the end of each day

    /* --------------------- End of var declarations -------------------- */

    srand(time(NULL)); // Seed the RNG

    /* -------------------------- Title Screen -------------------------- */

    displayTitle();

    switch (listMenu(aTitleOptions, 2, 52, 22))
    {
        case 0: // New Game
            intro();
            break;
        case 1: // Load Game: Show a list of save files and choose from them
            pFile = fopen("0.p5tb", "rt"); // The auto save
            if (pFile == NULL)
            {
                /* If the auto save does not exist, then the game has never
                been ran before. */
                locate(1, 26);
                printf("Error: No save files detected! Starting a new game...");
                printf("\n" TEXT_ANYKEY);
                captureInput();
                intro();
            }
            else
            {
                nSaveNum = loadFileMenu(36, 26);
                load(nSaveNum, &nLocation, &nDay, &nStartPeriod, &nYen,
                     &nBBBLv, &bLentMoney, aConfPts, aStatPts, aItems,
                     aItemsBoughtToday, aConfGifted, aConfGiftedToday);
                bSaveFileLoaded = true;
            }
            break;
    }

    /* -------------------------- Game Start ---------------------------- */

    /*
    Special event: we immediately unlock Sojiro even though he is normally
    only available in the evening
    */
    if (aConfPts[SOJIRO] == LOCKED) // i.e. only in a new game
    {
        triggerEvent(SOJIRO, UNLOCK_EVENT);
        aConfPts[SOJIRO] = CONF_LV1;
    }

    displayTutorial();
    displaySocialStats(aStatPts);
    // On a new game, nDay = 1, but loading a save file can change this
    for (nDay = nDay; nDay <= DAYS && !bQuit; nDay++)
    {
        /* -- A New Day Begins -- */
        displayMap();
        if (!bSaveFileLoaded)
        {
            nLocation = LEBLANC_CAFE;
            if (isWeekday(nDay))
            {
                nLocation = SHUJIN_ACADEMY;
            }
        }
        nHighlight = 0;
        // nStartPeriod is AFTERNOON unless loading a save file
        for (nPeriod = nStartPeriod; nPeriod <= EVENING  && !bQuit; nPeriod++)
        {
            /* -- A New Period Begins -- */

            /* If loading a save and starting at evening,
            start at afternoon next time */
            nStartPeriod = AFTERNOON;

            bTimePassed = false;
            bLocationChange = true;
            // Autosave: save to save slot #0
            save(0, nLocation, nDay, nPeriod, nYen, nBBBLv, bLentMoney,
                 aConfPts, aStatPts, aItems, aItemsBoughtToday, aConfGifted,
                 aConfGiftedToday);

            displayDateTime(nDay, nPeriod);
            while (!bTimePassed && !bQuit)
            {
                /* -----------------------------------------------------------
                                       Get player input
                ----------------------------------------------------------- */
                do
                {
                    // Update the screen
                    if (tryUnlockEvent(nLocation, nDay, nPeriod, aConfPts))
                    {
                        bDoRefresh = true;
                    }

                    if (bDoRefresh)
                    {
                        refreshScreen(nLocation, nDay, nPeriod, nYen,
                                      aConfPts, aStatPts, aActions, aItems,
                                      aConfGifted, aConfGiftedToday, nHighlight,
                                      bStatViewToggle);
                        bDoRefresh = false;
                    }

                    if (bLocationChange || bSaveFileLoaded || bGiftedConfidant)
                    {
                        markMap(nLocation, nDay, nPeriod, aConfPts,
                                aConfGiftedToday);
                        getActions(nLocation, nDay, nPeriod,
                                   aConfPts, aItems, aConfGiftedToday,
                                   aActions);
                        bLocationChange = false;
                        bSaveFileLoaded = false;
                        bResetFooter = true;
                    }

                    if (bResetFooter)
                    {
                        displayFooter("");
                        displayConfsHere(aActions, nLocation);
                        bResetFooter = false;
                    }

                    displayYen(nYen);
                    displayMenu(aActions, aItems);
                    highlightMenu(nHighlight, aActions, aItems, false);

                    do
                    {
                        nInput = captureInput();
                    } while (!isInRange(nInput, MAP_NORTH, MAP_WEST) &&
                             !isInRange(nInput, MENU_UP, MENU_DOWN) &&
                             nInput != SCREEN_REFRESH &&
                             nInput != STAT_TOGGLE &&
                             nInput != CONFIRM);

                    /* --------------------------------------------------------
                                Player pressed a keyboard key input
                    -------------------------------------------------------- */
                    if (isInRange(nInput, MAP_NORTH, MAP_WEST))
                    {
                        // is Move Input
                        nOldLocation = nLocation;
                        controlLocation(nInput, nDay, nPeriod, &nLocation);
                        if (nOldLocation != nLocation)
                        {
                            nHighlight = 0;
                            bLocationChange = true;
                        }
                    }
                    else if (isInRange(nInput, MENU_UP, MENU_DOWN))
                    {
                        // is Menu Input
                        controlHighlight(nInput, aActions, aItems, &nHighlight);
                        // bResetFooter = true;
                    }
                    else if (nInput == SCREEN_REFRESH)
                    {
                        bDoRefresh = true;
                    }
                    else if (nInput == STAT_TOGGLE)
                    {
                        bStatViewToggle = !bStatViewToggle;
                        displayStatScreen(bStatViewToggle, aConfPts, aStatPts,
                                          aConfGifted, aConfGiftedToday);
                    }

                } while (nInput != CONFIRM && !bQuit);

                /* -----------------------------------------------------------
                            Player selected something from the menu
                ----------------------------------------------------------- */

                highlightMenu(nHighlight, aActions, aItems, true);

                if (nHighlight < ACTION_MENU_LIMIT)
                {
                    // is highlighting action
                    // nSelection is an action
                    nSelection = aActions[nHighlight];
                    if (isConfAction(nSelection))
                    {
                        bTimePassed = handleConfAct(nSelection, &nYen,
                                                    &bLentMoney, aItems,
                                                    aConfPts, aConfGifted,
                                                    aConfGiftedToday,
                                                    aStatPts,
                                                    &bDoRefresh,
                                                    &bGiftedConfidant);
                        if (bDoRefresh) // After Conf Max Event
                        {
                            refreshScreen(nLocation, nDay, nPeriod, nYen,
                                          aConfPts, aStatPts, aActions, aItems,
                                          aConfGifted, aConfGiftedToday,
                                          nHighlight, bStatViewToggle);
                            if (aConfPts[toConf(nSelection)] == CONF_MAX)
                            {
                                displayFooter(TEXT_MAXOUT);
                            }
                        }
                    }
                    else if (isInRange(nSelection, SHOP_SECOND_HAND, SHOP_BBB))
                    {
                        // is Shop Action
                        /* nAction - SHOP_SECOND_HAND: turns a shop action
                           into the corresponding shop */
                        shopAt(nSelection - SHOP_SECOND_HAND, aConfPts[TAE],
                               &nYen, aItems, aItemsBoughtToday);
                        bResetFooter = true;
                    }
                    else if (isInRange(nSelection, JOB_FLOWER, JOB_CONVENIENCE))
                    {
                        // is Job Action
                        bTimePassed = true;
                        handleJob(nSelection, aStatPts, &nYen);
                    }
                    else 
                    {
                        // is Stat Boost Action
                        bTimePassed = handleStatAct(nSelection, aStatPts,
                                                    aItems, &nYen,
                                                    &nBBBLv);
                        bResetFooter = !bTimePassed; // Remove act fail text
                    }
                }
                else if (nHighlight < ACTION_MENU_LIMIT + ITEM_MENU_LIMIT)
                {
                    // is highlighting item
                    displayItemDesc(aItems[nHighlight - ACTION_MENU_LIMIT]);
                    /* nHighlight - ACTION_MENU_LIMIT: index of the currently
                       selected item*/
                }
                else if (isInRange(nHighlight, 15, 16))
                {
                    // is highlighting save/load
                    handleSaveLoad(nHighlight, &nLocation, &nDay, &nPeriod,
                                   &nYen, &nBBBLv, &bLentMoney, aConfPts,
                                   aStatPts, aItems, aItemsBoughtToday,
                                   aConfGifted, aConfGiftedToday, &bDoRefresh,
                                   &bSaveFileLoaded);
                }
                else
                {
                    // Quit confirmation
                    displayFooter("Are you sure you want to quit? "
                                  "Unsaved progress will be lost!");
                    bQuit = askYesNo(2, FOOTER_Y + 1);
                }
            }
            // End of the Period: It is now EVENING unless the day has ended
            if (!bQuit)
            {
                printf("| Time has passed!\n| ");
                checkConfReqs(aStatPts, aConfPts);
                if (aItems[BOOST] != NONE &&
                   (aItems[BOOST] != BBB_COMBO || nPeriod == EVENING))
                {
                    // Reset BOOST item
                    aItems[BOOST] = NONE;
                    printf(TEXT_BOOST_WASTED);
                }
                printf("\n| " TEXT_ANYKEY);
                captureInput();
                nLocation = LEBLANC_CAFE;
			    nHighlight = 0;
			    bDoRefresh = true;
            }
        }
        // End of the Day
        if (!bQuit)
        {
            displayNextDay(nDay);
            /* Purchased gifts and upgrade items will always be considered
            "bought today" in order to prevent players from purchasing more
            than one of the same gift, hence why we start this for loop at
            HERBAL_SUPPLEMENT, the first boost item */
            for (nItem = HERBAL_SUPPLEMENT; nItem < AMOUNT_ITEMS; nItem++)
                aItemsBoughtToday[nItem] = false;
            set(aConfGiftedToday, AMOUNT_CONFIDANTS, false);
        }
    }
    // End of the Game
    if (!bQuit)
    {
        ending(aConfPts);
    }
    system("cls");
    printf("Thank you for playing the game!\n");
    return 0;
}
