/*
These functions handle most selections made in main(), mostly directing
them to the functions in game_actions.c.
*/

/*
    Handle job actions.
    @param nAction action ID representing a job action
    @param aStatPts social stat points
    @param pYen pointer to Yen
*/
void
handleJob (int nAction, int aStatPts[], int *pYen)
{
    switch (nAction)
    {
        case JOB_FLOWER:
            displayFooter(TEXT_J_FLOWER);
            break;
        case JOB_GYUDON:
            displayFooter(TEXT_J_GYUDON);
            break;
        case JOB_CONVENIENCE:
            displayFooter(TEXT_J_CONVEN);
            break;
    }
    jobEarn(aStatPts, nAction, pYen);
}

/*
    Handle confidant actions. If the player has a gift item, ask them to choose
    whether or not they want to give the gift or spend time with the confidant
    or not do anything. Otherwise, just spend time with the confidant.
    @param nAction action ID representing a job action
    @param pYen pointer to Yen
    @param pLentMoney bool representing if Yusuke owes the player
    @param aItems inventory
    @param aConfPts confidant points
    @param aConfGifted represents if any confidants have been gifted
    @param pDoRefresh represents if the screen should refresh
    @return `true` or `false` based on whether or not time has passed because
    of the action taken*/
int
handleConfAct (int nAction, int *pYen, int *pLentMoney, int aItems[],
               int aConfPts[], int aConfGifted[], int *pDoRefresh)
{
    int nConfActType = SPEND_TIME;
    int nConf = toConf(nAction);
    int nPrevConfPts;
    int bTimePassed = false;
    char sConf[CHR_LIMIT];
    copyConfName(sConf, nConf);

    if (aItems[GIFT] != NONE)
    {
        nConfActType = askConfActType(aItems[GIFT]);
        if (nConfActType == GIVE_GIFT)
        {
            if (aConfGifted[nConf] == false)
            {
                displayFooter("");
                printf("| You gave a gift to %s! \n", sConf);
                printf("| Since you gave %s a gift, %s will now be colored\n| ",
                        sConf, sConf);
                printf(FORE_YELLOW "yellow" COLOR_RESET " on the confidant stat"
                       " screen.\n| " TEXT_ANYKEY);
                captureInput();
                aItems[GIFT] = NONE;
                addConfPts(toConf(nAction), 3, aConfPts);
                aConfGifted[nConf] = true;
                *pDoRefresh = true; // update confidant stat screen
            }
            else
            {
                displayFooter(TEXT_GAVE_CONF_GIFT_ALREADY);
            }
        }
        else if (nConfActType == CANCEL_CONF)
            displayFooter("Cancelled.");
    }

    if (nConfActType == SPEND_TIME)
    {
        displayFooter("");
        /* Spending time with most confidants is free,
        but calling SADAYO costs Y100. */
        if (toConf(nAction) != SADAYO || pay(100, pYen))
        {
            bTimePassed = true;
            nConf = toConf(nAction);
            nPrevConfPts = aConfPts[nConf];
            hangout(nConf, aConfPts, aItems);
            /*
            Yusuke has a 30% chance of asking for Y300 for his train ride home.
            Lending Yen will net you +1 confidant points with him, and he will
            return the Yen next time you hang out with him.
            */
            if (nConf == YUSUKE)
            {
                if (!*pLentMoney && chance(30))
                {
                    printf(TEXT_YUSUKE_ASK);
                    if (askYesNo(3, FOOTER_Y + 5))
                    {
                        pay(300, pYen);
                        addConfPts(YUSUKE, 1, aConfPts);
                        *pLentMoney = true;
                    }
                }
                else if (*pLentMoney)
                {
                    printf(TEXT_YUSUKE_THANKS);
                    earn(300, pYen);
                    *pLentMoney = false;
                }
            }
            if (nPrevConfPts != CONF_MAX && aConfPts[nConf] == CONF_MAX)
            {
                *pDoRefresh = true; // Max event was triggered -- refresh screen
            }
        }
    }
    return bTimePassed;
}

/*
    Handle stat boosting actions.
    @param nAction action ID representing a stat boost action
    @param aStatPts social stat points
    @param aItems inventory
    @param pYen pointer to Yen
    @param pBBBLv BBB challenge level
    @return `true` or `false` based on whether or not time has passed because
    of the action taken
*/
int
handleStatAct (int nAction, int aStatPts[], int aItems[],
               int *pYen, int *pBBBLv)
{
    int bTimePassed = true;
    switch (nAction)
    {
        case DO_TRAIN:
            doStatBoost(aStatPts, GUTS, 1, aItems, PORK_TONKOTSU_BOWL,
                        TEXT_TRAIN);
            break;
        case DO_STUDY_LIBRARY:
            doStatBoost(aStatPts, KNOWLEDGE, 1, aItems, CHICKEN_KATSU_BOWL,
                        TEXT_LIBRARY);
            break;
        case DO_PLANTS:
            doStatBoost(aStatPts, KINDNESS, 1, aItems, HERBAL_ESSENCE,
                        TEXT_PLANTS);
            break;

        case DO_STUDY_LEBLANC:
            doStudyLeBlanc(aStatPts, aItems);
            break;

        case DO_CLEAN:
            doClean(aStatPts, aItems);
            break;

        /* -------------------------------------------------------------
            If the actions below were selected but cannot be done,
            (e.g. because no DVDs, not enough Yen, too full for BBB Challenge)
            then time doesn't pass
           ------------------------------------------------------------- */

        case DO_WATCH_DVD:
            bTimePassed = doWatchDVD(aStatPts, aItems);
            break;

        case DO_CAFE:
            bTimePassed = doPaidStatBoost(aStatPts,
                                          KNOWLEDGE, 1 + chance(50),
                                          pYen, 1000,
                                          aItems, CHICKEN_KATSU_BOWL,
                                          TEXT_CAFE);
            break;
        case DO_FITNESS:
            bTimePassed = doPaidStatBoost(aStatPts,
                                          GUTS, toStatLv(aStatPts[GUTS]) + 1,
                                          pYen, 1500,
                                          aItems, PORK_TONKOTSU_BOWL,
                                          TEXT_FITNESS);
            break;
        case DO_RHYTHM:
            bTimePassed = doPaidStatBoost(aStatPts,
                                          KNOWLEDGE, 1 + chance(30),
                                          pYen, 100,
                                          aItems, CHICKEN_KATSU_BOWL,
                                          TEXT_RHYTHM);
            break;
        case DO_ZOMBIE:
            bTimePassed = doPaidStatBoost(aStatPts,
                                          GUTS, 1 + chance(30),
                                          pYen, 100, aItems, PORK_TONKOTSU_BOWL,
                                          TEXT_ZOMBIE);
            break;

        case DO_WARM_BATH:
            bTimePassed = doWarmBath(aStatPts, pYen, aItems);
            break;

        case DO_BBB_CHALLENGE:
            bTimePassed = doChallenge(aStatPts, pYen, aItems, pBBBLv);
            break;
    }
    return bTimePassed;
}

/*
    Handle save and load actions. If saving, player detail parameters would be
    saved to a file; if loading, file would be read into such parameters instead
    @param nHighlight currently selected top menu item
    @param pLocation pointer to player's location
    @param pDay pointer to the current day
    @param pPeriod pointer to the current period
    @param pYen pointer to yen
    @param pBBBLv pointer to the current BBB challenge level
    @param pLentMoney pointer to Yusuke's "owing us" state
    @param aConfPts confidant points
    @param aStatPts social stat points
    @param aItems inventory
    @param aItemsBoughtToday items the player has bought today (or
    upgrade or gift items the player has bought so far)
    @param aConfGifted whether or not any confidants have been gifted items
    this plathrough
    @param pDoRefresh whether the screen should refresh or not
    @param pSaveFileLoaded if a save file was loaded or not
*/
void
handleSaveLoad (int nHighlight, int *pLocation, int *pDay, int *pPeriod,
                int *pYen, int *pBBBLv, int *pLentMoney, int aConfPts[],
                int aStatPts[], int aItems[], int aItemsBoughtToday[],
                int aConfGifted[], int *pDoRefresh, int *pSaveFileLoaded)
{
    int nSaveNum;
    switch (nHighlight)
    {
        case 15: // Save
            displayFooter(BACK_YELLOW "Save File" COLOR_RESET);
            nSaveNum = saveFileMenu(20, FOOTER_Y);
            save(nSaveNum, *pLocation, *pDay, *pPeriod, *pYen, *pBBBLv,
                *pLentMoney, aConfPts, aStatPts, aItems, aItemsBoughtToday,
                aConfGifted);
            *pDoRefresh = true;
            break;
        case 16: // Load
            displayFooter(BACK_YELLOW "Load File" COLOR_RESET);
            nSaveNum = loadFileMenu(20, FOOTER_Y);
            load(nSaveNum, pLocation, pDay, pPeriod, pYen, pBBBLv,
                 pLentMoney, aConfPts, aStatPts, aItems, aItemsBoughtToday,
                 aConfGifted);
            *pSaveFileLoaded = true;
            *pDoRefresh = true;
            break;
    }
}