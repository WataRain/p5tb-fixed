/*
These are functions meant for the UI (display, control, etc.) 
*/

/*
    Set the terminal-drawing cursor position.
    @param x    column
    @param y    line
*/
void
locate (int x, int y)
{
    printf("\x1b[%d;%dH", y, x); // An escape sequence
}

/*
    Display the name of an item
    @param nItem item ID
*/
void
displayItem (int nItem)
{
    char sItemName[CHR_LIMIT];
    copyItemName(sItemName, nItem);
    if (nItem != NONE)
        printf("%s", sItemName);
}

/*
    Display the name of a confidant
    @param nConfidant confidant ID
*/
void
displayConf (int nConfidant)
{
    char sConfName[CHR_LIMIT];
    copyConfName(sConfName, nConfidant);
    printf("%s", sConfName);
}

/*
    Display the hangout text of a confidant. (These texts are displayed
    when spending time with that confidant)
    @param nConfidant confidant ID
*/
void
displayConfHangout (int nConfidant)
{
    switch (nConfidant)
        {
            case SOJIRO:
                displayFooter("You helped Sojiro take care of the cafe!\n");
                break;
            case RYUJI:
                displayFooter("You had fun being with Ryuji!\n");
                break;
            case ANN:
                displayFooter("You had fun shopping with Ann!\n");
                break;
            case YUSUKE:
                displayFooter("You had a fun time chilling with Yusuke.\n");
                break;
            case MAKOTO:
                displayFooter("You read books with Makoto.\n");
                break;
            case FUTABA:
                displayFooter("You had fun playing with Futaba!\n");
                break;
            case HARU:
                displayFooter("You spent some time with Haru.\n");
                break;
            case TAE:
                displayFooter("You helped Takemi with her research.\n");
                break;
            case SADAYO:
                displayFooter("You received some pointers from Kawakami!\n");
                break;
            case SUMIRE:
                displayFooter("You trained with Sumire! What moves!\n");
                break;
            default:
                displayFooter("Confidant hangout text not found\n");
        }
}


/*
    Display the name of a stat
    @param nStat social stat ID
*/
void
displayStat (int nStat)
{
    char aStatNames[3][CHR_LIMIT] = {"Kindness", "Guts", "Knowledge"};
    printf("%s", aStatNames[nStat]);
}

/*
    Display the day of the week corresponding to `nDay`
    @param nDay in-game day count
*/
void
displayDayOfWeek (int nDay)
{
    char aDayNames[7][CHR_LIMIT] = {
        FORE_RED "Sunday   " COLOR_RESET,
        "Monday   ", "Tuesday  ", "Wednesday", "Thursday ", "Friday   ",
        FORE_BLUE "Saturady " COLOR_RESET
        };
    printf("%s", aDayNames[toDayOfWeek(nDay)]);
}

/*
    Display the shop name of `nShop`.
    @param nShop shop ID
*/
void
displayShopName (int nShop)
{
    char aShopNames[][CHR_LIMIT] = {
        BACK_GREEN "Second Hand Shoppe" COLOR_RESET,
        BACK_BLUE "Vitamin Shop" COLOR_RESET,
        FORE_YELLOW "Tonkotsu King" COLOR_RESET,
        BACK_RED "Gift Shop" COLOR_RESET,
        BLACK_ON_WHITE "DVD Shop" COLOR_RESET,
        FORE_YELLOW BACK_RED "Big Bang Burger" COLOR_RESET
    };
    displayFooter(aShopNames[nShop]);
}

/*
    Display the item description for `nItem`
    @param nItem item ID
*/
void
displayItemDesc (int nItem)
{
    char sItemName[CHR_LIMIT];
    char sItemDesc[CHR_LIMIT];
    copyItemName(sItemName, nItem);
    copyItemDesc(sItemDesc, nItem);
    displayFooter(sItemName);
    printf("| %s\n", sItemDesc);
}

/*
    Capture a key press on the keyboard and
    map it to the appropriate input event.
    @return an integer representing an input event, e.g. `MENU_UP`, `MOVE_NORTH`
*/
int
captureInput ()
{
    char cInput;
    int nInputEvent = NONE;
    fflush(stdin);
    cInput = getch();
    if (cInput == ARROW_START) // SIGNAL: ARROW KEY WAS PRESSED
    {
        cInput = getch();
        switch (cInput)
        {
            case UP: // UP ARROW
                nInputEvent = MENU_UP;
                break;
            case DOWN: // DOWN ARROW
                nInputEvent = MENU_DOWN;
                break;
            // case LEFT: // LEFT ARROW
            //     nInputEvent = MENU_LEFT;
            //     break;
            // case RIGHT: // RIGHT ARROW
            //     nInputEvent = MENU_RIGHT;
            //     break;
            default:
                nInputEvent = NONE;
        }
    }
    else
    {
        switch (cInput)
        {
            case 'w':
            case 'W':
                nInputEvent = MAP_NORTH;
                break;
            case 's':
            case 'S':
                nInputEvent = MAP_SOUTH;
                break;
            case 'a':
            case 'A':
                nInputEvent = MAP_WEST;
                break;
            case 'd':
            case 'D':
                nInputEvent = MAP_EAST;
                break;
            case ENTER:
                nInputEvent = CONFIRM;
                break;
            case 'r':
            case 'R':
                nInputEvent = SCREEN_REFRESH;
                break;
            case 't':
            case 'T':
                nInputEvent = STAT_TOGGLE;
                break;
            default:
                nInputEvent = NONE;
                break;
        }
    }
    return nInputEvent;
}

/*
    Ask the player to choose from a list of options.
    @param aOptions array of strings representing options
    @param nSize amount of options
    @param x column to begin drawing the list menu
    @param y line to begin drawing the list menu
    @return an integer from 0 to `nSize` representing the choice of the player
*/
int
listMenu (char aOptions[][CHR_LIMIT], int nSize, int x, int y)
{
    int nInput;
    int nChoice = 0;
    do
    {
        for (int i = 0; i < nSize; i++)
        {
            locate(x, y + i);
            printf("%s %s" COLOR_RESET,
                   (i == nChoice) ? BACK_RED ">": " ",
                   aOptions[i]);
        }
        nInput = captureInput();
        switch (nInput)
        {
            case MENU_UP:
                do
                {
                    nChoice -= 1;
                    nChoice = (nChoice + nSize) % nSize; // wraparound
                } while (strlen(aOptions[nChoice]) == 0); // Skip blank items
                break;
            case MENU_DOWN:
                do
                {
                    nChoice += 1;
                    nChoice = (nChoice + nSize) % nSize; // wraparound
                } while (strlen(aOptions[nChoice]) == 0); // Skip blank items
                break;
        }
    } while (nInput != CONFIRM);
    locate(x, y + nChoice);
    printf(BACK_GRAY "> %s" COLOR_RESET, aOptions[nChoice]);
    return nChoice;
}

/*
    Draw a yes/no menu. Return true/false if answered with yes/no respectively
    @param x column to begin drawing the list menu
    @param y line to begin drawing the list menu
    @return `true` if the player responds with Yes, `false` otherwise
*/
int
askYesNo (int x, int y)
{
    char aOptions[2][CHR_LIMIT] = {"No", "Yes"};
    int nChoice;
    nChoice = listMenu(aOptions, 2, x, y);
    return nChoice;
}

/*
    Ask the player if they would like to present a gift, spend time with the
    confidant, or not do anything. Should appear only when the player has a gift
    @param nGift item id of the gift
    @return integer from 0 to 2 based on the player's action.
    `0`: Present the gift to the confidant
    `1`: Spend time with the confidant
    `2`: Nevermind (no action will be taken)
*/
int
askConfActType (int nGift)
{
    char aOptions[3][CHR_LIMIT] = {
        "Present the gift to the confidant",
        "Spend time with the confidant",
        "Nevermind"};

    displayFooter("");
    locate(1, FOOTER_Y);
    printf("| You have a ");
    displayItem(nGift);
    printf(".\n| Do you want to give it, or just spend time with ");
    printf("the confidant?");

    return listMenu(aOptions, 3, 2, FOOTER_Y+3);
}

/*
    Mark the map by placing icons on it.
    [P]: Player; [C]: Available Confidant; [!] Unlockable Confidant
    @param nPlayerLocation    player's current location
    @param nDay         in-game day counter
    @param nPeriod      the current period (afternoon, evening)
    @param aConfPts[]   relationship points with every confidant
*/
void
markMap (int nPlayerLocation, int nDay, int nPeriod, int aConfPts[])
{
    // Coordinates of the map marks per place
    int locMarkX[AMOUNT_PLACES] = {10, 10, 10, 28, 28, 53, 46, 63, 46};
    int locMarkY[AMOUNT_PLACES] = {13, 18, 23, 18, 23,  4, 18, 18, 23};
    int aConfsHere[MAX_CONFS_IN_LOCATION];
    int i;
    int nConf;
    int bConfHereAndNow;
    int bMarked;

    for (int nLocation = 0; nLocation < AMOUNT_PLACES; nLocation++)
    {
        bMarked = false;
        locate(locMarkX[nLocation], locMarkY[nLocation]);
        if (nPlayerLocation == nLocation)
        {
            printf(COLOR_RESET BACK_RED "P" COLOR_RESET);
            bMarked = true;
        }
        else
        {
            getConfsHere(nLocation, aConfsHere);
            bConfHereAndNow = false;
            i = 0;
            do
            {
                nConf = aConfsHere[i];
                bConfHereAndNow = isConfActiveNow(nConf, nLocation, nDay,
                                                  nPeriod);
                if (bConfHereAndNow)
                {
                    if (aConfPts[nConf] >= CONF_LV1)
                    {
                        printf(FORE_YELLOW "C" COLOR_RESET);
                        bMarked = true;
                    }
                    else if (aConfPts[nConf] == UNLOCKABLE)
                    {
                        printf(FORE_YELLOW "!" COLOR_RESET);
                        bMarked = true;
                    }
                }
                i++;
            } while (!bMarked && i < 3);
            if (!bMarked)
                printf(" ");
        }
    }
}

/*
    Display the name of an action
    @param nAction action id
*/
void
displayAction (int nAction)
{
    switch (nAction)
    {
        case DO_STUDY_LEBLANC:
            printf("Study @ LeBlanc");
            break;
        case DO_WATCH_DVD:
            printf("Watch a DVD");
            break;
        case HANGOUT_SOJIRO:
            printf("Conf: Sojiro");
            break;
        case HANGOUT_FUTABA:
            printf("Conf: Futaba");
            break;
        case HANGOUT_SADAYO:
            printf("Conf (Y100): Call Ms.Kawakami");
            break;
        case SHOP_SECOND_HAND:
            printf("Shop: Second Hand Shoppe");
            break;
        case JOB_CONVENIENCE:
            printf("Job: Convenience Store");
            break;
        case DO_WARM_BATH:
            printf("Y500: Take a warm bath");
            break;
        case SHOP_VITAMINS:
            printf("Shop: Vitamin Store");
            break;
        case HANGOUT_TAE:
            printf("Conf: Takemi");
            break;
        case SHOP_TONKOTSU:
            printf("Shop: Tonkotsu Store");
            break;
        case HANGOUT_YUSUKE:
            printf("Conf: Yusuke");
            break;
        case SHOP_GIFT:
            printf("Shop: Gift Shop");
            break;
        case JOB_FLOWER:
            printf("Job: Flower Shop");
            break;
        case HANGOUT_ANN:
            printf("Conf: Ann");
            break;
        case DO_TRAIN:
            printf("Train @ Shujin Academy Gym");
            break;
        case HANGOUT_RYUJI_GYM:
            printf("Conf: Ryuji");
            break;
        case HANGOUT_SUMIRE:
            printf("Conf: Sumire");
            break;
        case DO_STUDY_LIBRARY:
            printf("Study @ Library");
            break;
        case HANGOUT_MAKOTO:
            printf("Conf: Makoto");
            break;
        case DO_CLEAN:
            printf("Clean the blackboard");
            break;
        case DO_PLANTS:
            printf("Tend to plants");
            break;
        case HANGOUT_HARU_GARDEN:
            printf("Conf: Haru");
            break;
        case SHOP_DVD:
            printf("Shop: DVD Shop");
            break;
        case DO_CAFE:
            printf("Y1000: Chill @ Nearby Cafe");
            break;
        case DO_FITNESS:
            printf("Y1500: Train @ Fitness Gym");
            break;
        case JOB_GYUDON:
            printf("Job: Gyudon Store");
            break;
        case DO_BBB_CHALLENGE:
            printf("Y1500: Big Bang Challenge");
            break;
        case SHOP_BBB:
            printf("Shop: Big Bang Burger");
            break;
        case HANGOUT_HARU_BBB:
            printf("Conf: Haru");
            break;
        case DO_RHYTHM:
            printf("Y100: Play rhythm game");
            break;
        case DO_ZOMBIE:
            printf("Y100: Play zombie shooter");
            break;
        case HANGOUT_RYUJI_ARCADE:
            printf("Conf: Ryuji");
            break;
        case NONE:
        default:
            break;
    }
}

/*
    Display the side menu where the player can select actions and items, and
    toggle the confidant stat screen, and also quit the game.
    @param aActions[8] the available actions the player can perform
    @param aItems[8]   the items in the player's inventory
*/
void
displayMenu (int aActions[ACTION_MENU_LIMIT], int aItems[ITEM_MENU_LIMIT])
{
    int nMode = NONE;
    int nChangeMode = NONE;
    for (int line = 1; line <= 25; line++)
    {
        locate(76, line);
        switch (line)
        {
            case 1:
            case 25:
                printf("========================================");
                break;
            case 2:
                printf("Your move?");
                nChangeMode = ACTIONS;
                break;
            case 12:
                printf("Check your items");
                nChangeMode = ITEMS;
                break;
            case 10:
            case 19:
                nChangeMode = NONE;
                break;
            case 21:
                printf("Notebook");
                break;
            case 22:
                printf("  Save File");
                break;
            case 23:
                printf("  Load File");
                break;
            case 24:
                printf("  Quit");
                break;
        }
        if (nMode != NONE)
        {
            // Clear out the menu item then display the new item
            locate(78, line);
            printf("                                          "); 
            locate(78, line);
            switch (nMode)
            {
                case ACTIONS:
                    displayAction(aActions[line-3]);
                    break;
                case ITEMS:
                    displayItem(aItems[line-13]);
                    break;
            }
        }

        if (line != 1 && line != 25)
        {
            locate(115, line);
            printf("|");
        }

        nMode = nChangeMode;
    }
}

/*
    Change the currently highlighted top menu item based on the input event
    received.
    @param nKey input event
    @param aActions array of available actions
    @param aItems items
    @param pHighlight pointer to `nHighlight`, which represents the position of
    the currently highlighted top menu item
*/
void
controlHighlight (int nKey, int aActions[], int aItems[], int *pHighlight)
{
    int nDelta = 0;
    int bBlankItem;

    if (nKey == MENU_DOWN)
        nDelta = 1;
    else if (nKey == MENU_UP)
        nDelta = -1;
    do
    {
        (*pHighlight) += nDelta;
        *pHighlight = (*pHighlight + 18) % 18; // Wrap around

        // Check if we're now highlighting nothing
        if (*pHighlight < ACTION_MENU_LIMIT)
            bBlankItem = aActions[*pHighlight] == NONE;
        else if (*pHighlight < ACTION_MENU_LIMIT + ITEM_MENU_LIMIT)
            bBlankItem = aItems[*pHighlight - 8] == NONE;
        else
            bBlankItem = false;
    } while (bBlankItem);
}

/*
    Show a highlight on the currently selected top menu item.
    @param nHighlight represents the menu item to highlight
    @param aActions[] available actions: selected action is highlighted
    @param aItems[]   inventory: selected inventory item is highlighted
    @param bGrayedOut `true` if the selection must be grayed out (i.e., once the
    player selects something)
*/
void
highlightMenu (int nHighlight, int aActions[], int aItems[], int bGrayedOut)
{
    int nOffset = 3;
    for (int line = 3; line <= 24; line++)
    {
        if (line != 12 && line != 21) // "Item", "Command" headings are here
            locate(77, line);
        printf(COLOR_RESET " ");
    }

    if (nHighlight < ACTION_MENU_LIMIT) // Action
    {
        locate(77, nHighlight + nOffset);
        printf("%s>", (bGrayedOut) ? BACK_GRAY: BACK_RED);
        displayAction(aActions[nHighlight]);
    }
    else if (nHighlight < ACTION_MENU_LIMIT + ITEM_MENU_LIMIT) // Item
    {
        nOffset += 2;
        locate(77, nHighlight + nOffset);
        printf("%s>", (bGrayedOut) ? BACK_GRAY: FORE_BLACK BACK_GREEN);
        displayItem(aItems[nHighlight - 8]);
    }
    else // Option
    {
        nOffset += 4;
        locate(77, nHighlight + nOffset);
        printf("%s>", (bGrayedOut) ? BACK_GRAY: FORE_BLACK BACK_YELLOW);
        switch (nHighlight)
        {
            case 15:
                printf("Save File");
                break;
            case 16:
                printf("Load File");
                break;
            case 17:
                printf("Quit");
                break;
        }
    }
    printf(COLOR_RESET);
}

/*
    A list menu where the options are the four save slots.
    This is the "base function" used in both `saveFileMenu()` and
    `loadFileMenu()`.
    @param x column to start drawing the file menu in
    @param y line to start drawing the file menu in
    @return the save slot chosen by the player
*/
int
fileMenu (int x, int y)
{
    int i;
    int nChosenSave;
    int nLocation, nDay, nPeriod, nYen;
    char sSaveFileDesc[CHR_LIMIT]; // Save file description text
    char aSaveFileDescs[4][CHR_LIMIT];
    char sFileName[CHR_LIMIT]; // File names to open
    FILE *pFile;

    for (i = 0; i <= 4; i++)
    {
        // Create text to represent the save file in the file select
        sprintf(sFileName, "%d.p5tb", i);
        pFile = fopen(sFileName, "rt");
        if (pFile != NULL)
        {
            if (i==0)
                sprintf(sSaveFileDesc, "Auto Save:      ");
            else
                sprintf(sSaveFileDesc, "Manual Save #%d: ", i);
            fscanf(pFile, "%d %d %d %d", &nLocation, &nDay, &nPeriod, &nYen);
            sprintf(sSaveFileDesc, "%s %2d/%-2d",
                    sSaveFileDesc, toMonth(nDay), toDayOfMonth(nDay));

            if (nPeriod == AFTERNOON)
                sprintf(sSaveFileDesc, "%s (Afternoon) ", sSaveFileDesc);
            else
                sprintf(sSaveFileDesc, "%s (Evening)   ", sSaveFileDesc);
            sprintf(sSaveFileDesc, "%s Y%d", sSaveFileDesc, nYen);
            fclose(pFile);
            strcpy(aSaveFileDescs[i], sSaveFileDesc);
        }
        else
        {
            strcpy(aSaveFileDescs[i], "(no save file)");
        }
    }
    // Choose among the save files
    locate(x, y);
    printf("Choose a save file:\n");
    nChosenSave = listMenu(aSaveFileDescs, 4, x, y+1);
    return nChosenSave;
}

/*
    Let the player choose among save files that exist. Depends on `fileMenu()`
    for file selection, but doesn't return until the player selects a save
    file that exists.
    @param x column to start drawing the file menu in
    @param y line to start drawing the file menu in
    @return the save slot chosen by the player
*/
int
loadFileMenu (int x, int y)
{
    int nSaveNum;
    char sFileName[CHR_LIMIT];
    FILE *pFile;
    do
    {
        nSaveNum = fileMenu(x, y);
        sprintf(sFileName, "%d.p5tb", nSaveNum);
        pFile = fopen(sFileName, "rt");
    } while (pFile == NULL);
    fclose(pFile);    
    return nSaveNum;
}

/*
    Let the player choose among save slots. Depends on `fileMenu()`
    for file selection, and if the player selects a save file that exists, the
    user will be warned that this save file will be overwritten, and asks for
    confirmation.
    @param x column to start drawing the file menu in
    @param y line to start drawing the file menu in
    @return the save slot chosen by the player
*/
int
saveFileMenu (int x, int y)
{
    int nSaveNum;
    int bConfirm = false;
    char sFileName[CHR_LIMIT];
    FILE *pFile;

    do
    {
        nSaveNum = fileMenu(x, y);
        sprintf(sFileName, "%d.p5tb", nSaveNum);
        pFile = fopen(sFileName, "rt");
        if (pFile != NULL)
        {
            locate(x, y+6);
            printf("Warning: A save file already exists at this slot.");
            locate(x, y + 7);
            printf("OK to overwrite?");
            bConfirm = askYesNo(x, y + 8);
        }
    } while (pFile != NULL && !bConfirm);
    fclose(pFile);

    return nSaveNum;
}

/*
    Display date time info (overlaid on the map)
    @param nDay in-game day counter
    @param nPeriod current period (afternoon, evening)
*/
void
displayDateTime (int nDay, int nPeriod)
{
    locate(4, 3);
    // Print date
    printf("%d/%d ", toMonth(nDay), toDayOfMonth(nDay));
    displayDayOfWeek(nDay);

    locate(4, 4);
    switch(nPeriod)
    {
        case AFTERNOON:
            printf("Afternoon");
            break;
        case EVENING:
            printf("Evening  ");
            break;
    }

    locate(4, 6);
    printf("%d day%s before ", DAYS - nDay + 1, (nDay == 60) ? "" : "s");
    locate(4, 7);
    printf("the incident");
}

/*
    Display the yen in the menu
    @param nYen
*/
void
displayYen (int nYen)
{
    locate(4, 9);
    printf("%10d Yen", nYen);
}

/*
    Reset the footer and display text in it, if any.
    @param sText text string to display in the footer
*/
void
displayFooter (char *sText)
{
    // Clear the footer area
    locate(1, FOOTER_Y);
    for (int i = 0; i < 10; i++)
    {
        printf("|");
        for (int j = 0; j < 73; j++)
            printf(" ");
        printf("|\n");
    }
    // Draw bottom border
    for (int i = 0; i < 115; i++)
        printf("=");

    locate(1, FOOTER_Y);
    if (strcmp(sText, "") != 0) // if text is not blank, then print it
    {
        printf("| %s\n", sText);
    }
}

/*
    Display the tutorial text at the bottom of the footer.s
*/
void
displayTutorial ()
{
    locate(1, FOOTER_Y+11);
    printf(TEXT_HELP);
}

/*
    Let all interactable confidants greet Ren.
    @param aActions available actions (where available confidants are)
    @param nLocation current location (used for Ryuji and Haru)
*/
void
displayConfsHere (int aActions[], int nLocation)
{
    int nAction;
    int nConfidant;
    locate(1,  FOOTER_Y);
    for (int i = 0; i < ACTION_MENU_LIMIT; i++)
    {
        nAction = aActions[i];
        if (isConfAction(nAction))
        {
            nConfidant = toConf(nAction);
            printf("| " FORE_YELLOW);
            switch (nConfidant)
            {
                case SOJIRO:
                    printf(TEXT_FLAVOR_SOJIRO);
                    break;
                case RYUJI:
                    if (nLocation == SHUJIN_ACADEMY)
                        printf(TEXT_FLAVOR_RYUJI_SHUJIN);
                    else
                        printf(TEXT_FLAVOR_RYUJI_ARCADE);
                    break;
                case ANN:
                    printf(TEXT_FLAVOR_ANN);
                    break;
                case YUSUKE:
                    printf(TEXT_FLAVOR_YUSUKE);
                    break;
                case MAKOTO:
                    printf(TEXT_FLAVOR_MAKOTO);
                    break;
                case FUTABA:
                    printf(TEXT_FLAVOR_FUTABA);
                    break;
                case HARU:
                    if (nLocation == SHUJIN_ACADEMY)
                        printf(TEXT_FLAVOR_HARU_SHUJIN);
                    else
                        printf(TEXT_FLAVOR_HARU_BBB);
                    break;
                case TAE:
                    printf(TEXT_FLAVOR_TAE);
                    break;
                case SADAYO:
                    printf(TEXT_FLAVOR_SADAYO);
                    break;
                case SUMIRE:
                    printf(TEXT_FLAVOR_SUMIRE);
                    break;
                default:
                    printf("A confidant is here.\n", nConfidant);
                    break;
            }
            printf(COLOR_RESET);
        }
    }
}

/*
    Display a progress bar                               123456789
    @param nWidth width of the bar e.g. nWidth = 9 --> `[|||||||||]`
    @param nProgress current progress e.g. the 10 in 10/100
    @param nMaxProgress maximum progress e.g. the 100 in 10/100
*/
void
displayProgressBar (int nWidth, int nProgress, int nMaxProgress)
{
    int nProgressWidth = 1.0 * nProgress / nMaxProgress * nWidth;
    int nSpaceWidth = nWidth - nProgressWidth;
    printf("[" FORE_RED);
    for (int i = 0; i < nProgressWidth; i++)
        printf("|");
    printf(COLOR_RESET);
    for (int j = 0; j < nSpaceWidth; j++)
        printf(" ");
    printf("]");
}

/*
    Clear the stats screen to make space for either social or confidant stats
*/
void
clearStatsScreen ()
{
    for (int i = 26; i <= 35; i++)
    {
        locate(UI_RIGHT_X, i);
        printf("                                       |");
    }
}

/*
    Display the social stats screen
    @param aStatPts social stat points
*/
void
displaySocialStats (int aStatPts[])
{
    int nBaseY;
    int nStatPts;
    int nStatLv;
    int nToNextLv;
    int nToPrevLv;
    char aRankNames[AMOUNT_STATS][4][CHR_LIMIT] = {
        // Kindness
        {"Inoffensive", "Considerate", "Selfless", "Angelic"},
        // Guts
        {"Milquetoast", "Bold", "Dauntless", "Lionhearted"},
        // Knowledge
        {"Oblivious", "Learned", "Encyclopedic", "Erudite"}
    };

    clearStatsScreen();
    locate(UI_RIGHT_X, FOOTER_Y);
    printf("Social Stats");
    for (int nStat = KINDNESS; nStat <= KNOWLEDGE; nStat++)
    {
        nStatPts = aStatPts[nStat];
        nStatLv = toStatLv(nStatPts);
        nToNextLv = toStatNextLv(nStatPts);
        nToPrevLv = toStatPrevLv(nStatPts);
        nBaseY = 3 * nStat + 27;

        locate(77, nBaseY);
        displayStat(nStat);
        printf(" Lv %d - %s", toStatLv(nStatPts), aRankNames[nStat][nStatLv]);
        locate(77, nBaseY + 1);
        if (nStatLv == 3) // If level 3
        {
            printf("[" FORE_YELLOW "  MAXED OUT!!!  " COLOR_RESET "]");
        }
        else
        {
            displayProgressBar(16, nStatPts - nToPrevLv, nToNextLv - nToPrevLv);
            printf(" To Next Level: %-2d", toStatNextLv(nStatPts) - nStatPts);
        }
    }
}

/*
    Display the confidant stat screen. This screen contains information about
    the current confidant points accrued for each confidant, the points needed
    to reach the next rank with each confidant, and whether or not the confidant
    has been gifted in the current playthrough.
    @param aConfPts confidant relationship points
    @param aConfGifted `aConfGifted[nConf] == true` for all confidants `nConf`
    that have been gifted before
*/
void
displayConfStats (int aConfPts[], int aConfGifted[])
{
    int nConfPts;
    int nConfLv;
    int nConfToNextLv;
    int nConfToPrevLv;
    char sConfName[CHR_LIMIT];
    clearStatsScreen();
    for (int nConfidant = SOJIRO; nConfidant < AMOUNT_CONFIDANTS; nConfidant++)
    {
        nConfPts = aConfPts[nConfidant];
        nConfLv = toConfLv(nConfPts);
        nConfToNextLv = toConfNextLv(nConfPts);
        nConfToPrevLv = toConfPrevLv(nConfPts);
        locate(UI_RIGHT_X, FOOTER_Y+nConfidant);
        copyConfName(sConfName, nConfidant);
        printf("%s%8s" COLOR_RESET,
               (aConfGifted[nConfidant] == true) ? FORE_YELLOW : "", sConfName);
        if (nConfPts != CONF_MAX)
            printf(" Lv%d ", nConfLv);
        else
            printf(FORE_RED " MAX " COLOR_RESET);

        if (nConfPts >= CONF_LV1 && nConfPts < CONF_LV3)
        {
            displayProgressBar(12, nConfPts - nConfToPrevLv, nConfToNextLv - nConfToPrevLv);
            printf(" Next Lv: %-2d", nConfToNextLv - nConfPts);
        }
        else if (nConfPts == CONF_LV3)
        {
            printf("Max Event Available!");
        }
        else if (nConfPts == CONF_MAX)
        {
            printf("[" FORE_RED "<3<3<3<3<3<3" COLOR_RESET "]");
        }
        else
            printf("[Undiscovered]            ");
        printf("\n");
    }
}

/*
    Display a screen to transition to the next day. Specifically, the screen
    shows the previous and succeeding dates relative to the current day,
    and then shows the same relative to the next day.
    @param nDay the day (which will advance to the next day)
*/
void
displayNextDay (int nDay)
{
    int nDayToShow;
    for (nDayToShow = nDay; nDayToShow <= nDay + 1; nDayToShow++)
    {
        system("cls");
        printf(COLOR_RESET);

        // Year and month
        locate(8, 4);
        printf(BLACK_ON_WHITE "20XX %d" COLOR_RESET, toMonth(nDayToShow));

        // Days of the month
        locate(50, 13);
        printf("%-2d", toDayOfMonth(nDayToShow - 1));
        locate(50, 14);
        displayDayOfWeek(nDayToShow - 1);

        locate(57, 16);
        printf("%-2d ", toDayOfMonth(nDayToShow));
        if (nDayToShow == nDay + 1)
            printf("<-+");

        locate(57, 17);
        displayDayOfWeek(nDayToShow);
        printf(COLOR_RESET);

        if (nDayToShow + 1 != 62) // October 32 -- we don't need to show this
        {
            locate(64, 13);
            printf("%-2d", toDayOfMonth(nDayToShow + 1));
            locate(64, 14);
            displayDayOfWeek(nDayToShow + 1);
        }
        else
        {
            locate(64, 13);
            printf("The");
            locate(64, 14);
            printf(FORE_RED "PRESENT DAY" COLOR_RESET);
        }
        locate(70, 19);
        printf(TEXT_ANYKEY);
        captureInput();
    }
    system("cls");
}

/*
    Display the title screen
*/
void
displayTitle ()
{
    system("cls");
    locate(42, 10);
    printf(" ####    ###### " FORE_RED " #######  #### " COLOR_RESET);
    locate(42, 11);
    printf("#    #   #      " FORE_RED "    #         #" COLOR_RESET);
    locate(42, 12);
    printf("#    #   #      " FORE_RED "    #         #" COLOR_RESET);
    locate(42, 13);
    printf("#####    #####  " FORE_RED "    #     #### " COLOR_RESET);
    locate(42, 14);
    printf("#             # " FORE_RED "    #         #" COLOR_RESET);
    locate(42, 15);
    printf("#             # " FORE_RED "    #         #" COLOR_RESET);
    locate(42, 16);
    printf("#        #####  " FORE_RED "    #     #### " COLOR_RESET);
    locate(42, 17);
    printf("                " FORE_RED "               " COLOR_RESET);
    locate(42, 18);
    printf("  Persona   5   " FORE_RED "  Text - Based " COLOR_RESET);
    locate(54, 20);
    printf("by " FORE_YELLOW "J R G" COLOR_RESET);
}

/*
    Display the map
*/
void
displayMap ()
{
    locate(1, 1);
    printf("===========================================================================\n");
    printf("|                                   +----------------------------------+  |\n");
    printf("|                          /-------->         Shujin   Academy         |  |\n");
    printf("|                          |-------->              [ ]                 |  |\n");
    printf("|                          ||       | +---+   +-------+   +----------+ |  |\n");
    printf("|                          ||       | |Gym|   |Library|   |Class Room| |  |\n");
    printf("|                          ||       | |   |   |       |   |          | |  |\n");
    printf("|                          ||       | +---+   +-------+   +----------+ |  |\n");
    printf("|                          ||       +----------+  +------+  +----------+  |\n");
    printf("|                          ||                  |  |Garden|  |             |\n");
    printf("|  +------------+          ||                  |  |      |  |             |\n");
    printf("|  |LeBlanc Cafe|          ||                  |  +------+  |             |\n");
    printf("|  |    [ ]     |          ||                  |            |             |\n");
    printf("|  +-----^------+          ||                  +------------+             |\n");
    printf("|        |                 ||                                             |\n");
    printf("|   +----v-----+     +-----vv------+     +-------+     +---------------+  |\n");
    printf("|   |Back Alley<----->Train Station<----->Shibuya<----->Big Bang Burger|  |\n");
    printf("|   |   [ ]    <----->    [ ]      <----->  [ ]  |     |     [ ]       |  |\n");
    printf("|   +----^-----+     +-----^^------+     +---^---+     +---------------+  |\n");
    printf("|        |                 ||                |                            |\n");
    printf("|     +--v---+     +-------vv-------+     +--v---+                        |\n");
    printf("|     |Clinic|     |Underground Mall|     |Arcade|                        |\n");
    printf("|     | [ ]  |     |      [ ]       |     | [ ]  |                        |\n");
    printf("|     +------+     +----------------+     +------+                        |\n");
    printf("===========================================================================\n");

    locate(53, 21);
    printf("Legend");
    locate(55, 22);
    printf(FORE_RED "P Player location");
    locate(55, 23);
    printf(FORE_YELLOW "C Confidant");
    locate(55, 24);
    printf("! New confidant" COLOR_RESET);
}

/*
    Display the stat screen
    @param bStatViewToggle indicates which stat screen to draw
    @param aConfPts confidant points
    @param aStatPts social stat points
    @param aConfGifted confidant gifted status
*/
void
displayStatScreen (int bStatViewToggle, int aConfPts[], int aStatPts[],
                   int aConfGifted[])
{
    if (bStatViewToggle)
        displaySocialStats(aStatPts);
    else
        displayConfStats(aConfPts, aConfGifted);
}

/*
    Refresh the entire screen, i.e., redraw the UI
    @param nLocation pointer to player's location
    @param nDay pointer to the current day
    @param nPeriod pointer to the current period
    @param nYen pointer to yen
    @param aConfPts confidant points
    @param aStatPts social stat points
    @param aActions available actions in the current location
    @param aItems inventory
    @param aConfGifted confidant gifted status
    @param nHighlight position of the current top menu selection
    @param bStatViewToggle indicates which stat screen to draw
*/
void
refreshScreen (int nLocation, int nDay, int nPeriod, int nYen, int aConfPts[],
               int aStatPts[], int aActions[], int aItems[], int aConfGifted[],
               int nHighlight, int bStatViewToggle)
{
    system("cls");
    displayMap();
    markMap(nLocation, nDay, nPeriod, aConfPts);
    displayFooter("");
    displayDateTime(nDay, nPeriod);
    displayYen(nYen);
    displayConfsHere(aActions, nLocation);
    displayMenu(aActions, aItems);
    highlightMenu(nHighlight, aActions, aItems, false);
    displayStatScreen(bStatViewToggle, aConfPts, aStatPts, aConfGifted);
    displayTutorial();
}
