/*
These are the functions used in Persona 5: Text-Based that are not for the
UI; they do more than just display text on the screen. 
*/

// Prototypes
void displayFooter(char *text);
void displayConf(int nConfidant);
void displayStat(int nStat);
int captureInput();

/* Inside this file:
I. Integer Returning Functions
II. Boolean Returning Functions
III. Miscellaneous Game Functions
*/


/* ------------------------------------ */
/* -- I. Integer Returning Functions -- */
/* ------------------------------------ */


/*
    This function returns a random integer restricted to a certain range.
    Precondition: `nMin < nMax`
    @param nMin the lower bound of the random integer
    @param nMax the upper bound of the random integer  
    @return a random integer from `nMin` to `nMax`.
*/
int
randInt (int nMin, int nMax)
{
    return rand() % (nMax - nMin) + nMin;
}

/*
    This function converts the current `nDay` to an integer representing
    the corresponding day of the week, where `nDay = 1` is `SUNDAY (0)`.
    Precondition: `nDay > -6`, i.e., `nDay + 6` is strictly positive
    @param nDay in-game day count
    @return integers from `0 (SUNDAY)` to `6 (SATURDAY)`
*/
int
toDayOfWeek (int nDay)
{
    return (nDay + 6) % 7;
}

/*
    Convert the current `nDay` to its corresponding playable
    month, i.e., `9 (SEPTEMBER)` or `10 (OCTOBER)`.
    September has 30 days, so `nDay = 31` and onward
    should return `10 (OCTOBER)`.

    Precondition:
        `nDay` is within the playable amount of days, i.e., `1 <= nDay <= 60`
    @param nDay in-game day count
    @return `9 (SEPTEMBER)` or `10 (OCTOBER)`
*/
int
toMonth (int nDay)
{
    return  9 + nDay / 31;
}

/*
    Convert the current `nDay` to the day of the month
    In a new game, we begin at `nDay = 1`.
    August has 31 days, so `nDay = 0` means it is August 31

    September has 30 days, so `nDay = 1` means it is September 1, and
    `nDay = 31` means it is October 1.

    October has 31 days, so `nDay = 61` means it is October 31.
    (October 31 marks the end of the game)

    Precondition:
        `0 <= nDay <= 61`.
        * `toDayOfMonth()` indeed accepts 0 and 61, unlike `toMonth()`
           This is because `displayNextDay()` shows the days of the month
           before and after the current and succeeding nDay
           (i.e., from `nDay - 1` to `nDay + 2`).
        *  Technically speaking, `toMonth(0)` would return September
           instead of August, but toMonth()'s precondition prevents that.
*/
int
toDayOfMonth(int nDay)
{
    return (nDay == 0 || nDay == 61) ? 31 : (nDay + 29) % 30 + 1;
}

/*
    Return the corresponding level of a certain amount of social stat points
    @param nStatPts the amount of stat points to convert to its level
    @return An integer from 0-3 representing the current level of a stat
    from level 0-3
*/
int
toStatLv (int nStatPts)
{
    int nStatLv = 3;
    if (nStatPts < SOCIAL_LV1)
        nStatLv = 0;
    else if (nStatPts < SOCIAL_LV2)
        nStatLv = 1;
    else if (nStatPts < SOCIAL_LV3)
        nStatLv = 2;
    return nStatLv;
}

/*
    Get the points accrued previously to achieve the current level of a stat.
    @param nStatPts stat points
    @return the corresponding level of `nStatPts`
*/
int
toStatPrevLv (int nStatPts)
{
    int nStatPrevLv;
    switch (toStatLv(nStatPts))
    {
        case 0:
            nStatPrevLv = 0;
            break;
        case 1:
            nStatPrevLv = SOCIAL_LV1;
            break;
        case 2:
            nStatPrevLv = SOCIAL_LV2;
            break;
        case 3:
            nStatPrevLv = SOCIAL_LV3;
            break;
    }
    return nStatPrevLv;
}

/*
    Get the points required to achieve the next level of a stat.
    @param nStatPts stat points
    @return the corresponding level of `nStatPts`
*/
int
toStatNextLv (int nStatPts)
{
    int nStatNextLv;
    switch (toStatLv(nStatPts))
    {
        case 0:
            nStatNextLv = SOCIAL_LV1;
            break;
        case 1:
            nStatNextLv = SOCIAL_LV2;
            break;
        case 2:
        case 3:
            nStatNextLv = SOCIAL_LV3;
            break;
    }
    return nStatNextLv;
}

/*
    Returns the lowest stat level among the player's stats.
    That is, for
    `aStatPts[KINDNESS] = 0; aStatPts[GUTS] = 12; aStatPts[KNOWLEDGE] = 5`,
    `minStatLv(aStatPts)` would return `0`, alluding to `KINDNESS`
    having no points and therefore being Level 0
    @param aStatPts[] array representing the social stat points
    @return the lowest stat level
*/
int
minStatLv (int aStatPts[])
{
    int nMinLv = 4; // Would always decrease given that the max level is Lv. 3
    int nNewLv;
    for (int nStat = KINDNESS; nStat < AMOUNT_STATS; nStat++)
    {
        nNewLv = toStatLv(aStatPts[nStat]);
        if (nMinLv > nNewLv)
            nMinLv = nNewLv;
    }
    return nMinLv;
}

/*
Return the corresponding level of a certain amount of confidant points
@param nConfPts the amount of confidant points to convert to its level
*/
int
toConfLv (int nConfPts)
{
    int nConfLv = 4;
    if (nConfPts < CONF_LV1)
        nConfLv = 0;
    else if (nConfPts < CONF_LV2)
        nConfLv =  1;
    else if (nConfPts < CONF_LV3)
        nConfLv =  2;
    else if (nConfPts < CONF_MAX)
        nConfLv =  3;
    return nConfLv;
}

/*
Get the points required to achieve the next level of a confidant relationship.
*/
int
toConfNextLv (int nConfPts)
{
    int nConfNextLv;
    switch (toConfLv(nConfPts))
    {
        case 0:
            nConfNextLv = CONF_LV1;
            break;
        case 1:
            nConfNextLv = CONF_LV2;
            break;
        case 2:
        case 3: // Lv 3 cant advance to max without spending time w/them again
            nConfNextLv = CONF_LV3;
            break;
        case 4:
            nConfNextLv = CONF_MAX;
            break;
    }
    return nConfNextLv;
}

/*
Get the points required to achieve the current level of a confidant relationship.
*/
int
toConfPrevLv (int nConfPts)
{
    int nConfPrevLv;
    switch (toConfLv(nConfPts))
    {
        case 0: // Locked or unlockable
        case 1:
            nConfPrevLv = CONF_LV1;
            break;
        case 2:
            nConfPrevLv = CONF_LV2;
            break;
        case 3:
            nConfPrevLv = CONF_LV3;
            break;
        case 4:
            nConfPrevLv = CONF_MAX;
            break;
    }
    return nConfPrevLv;
}

/*
    Convert a confidant hangout action `nAction`
    to its corresponding confidant ID.
    Precondition: `nAction` is an int from 0 to 11, which are the Action IDs
                  of the confidant actions.
    @param nAction an action ID
    @returns the corresponding confidant associated with the action
*/
int
toConf (int nAction)
{
    /*
    Normally, a confidant action ID is the same as its associated confidant ID
        HANGOUT_SOJIRO (Action #0) --> Confidant SOJIRO (Confidant #0)
    But there are special cases, namely:
        HANGOUT_RYUJI_ARCADE (10)  --> RYUJI (1)
        HANGOUT_HARU_BBB (11)      --> HARU (6)
    */
    int nConf;
    switch (nAction)
    {
        case HANGOUT_RYUJI_ARCADE:
            nConf = RYUJI;
            break;
        case HANGOUT_HARU_BBB:
            nConf = HARU;
            break;
        default:
            nConf = nAction; 
            break;
    }
    return nConf;
}

/* -------------------------------------- */
/* -- II. Boolean Returning Functions --  */
/* -------------------------------------- */

/*
    Return true `nOdds` percent of the time.
    @param nOdds The odds of returning true, over 100 percent
    @return `true` or `false` randomly, with an `nOdds`% of returning `true`
*/
int
chance (int nOdds)
{
    return randInt(1, 100) <= nOdds;
}

/*
    Check if an integer `nX` is within `nMin` and `nMax`, inclusive
    @param nX   the integer to check inclusivity for
    @param nMin the lower bound
    @param nMax the upper bound
    @return `true` if `nX` was within the lower and upper bounds
*/
int
isInRange (int nX, int nMin, int nMax)
{
    return nX >= nMin && nX <= nMax;
}

/*
    Check if an int `nX` is inside an array `aInts`
    @param nX integer to check for
    @param aInts an integer array
    @param nSize size of the integer array
    @return `true` if `nX` was found inside `aInts`
*/
int
in (int nX, int aInts[], int nSize)
{
    int i;
    int bIsIn = false;
    for (i = 0; i < nSize && !bIsIn; i++)
    {
        if (nX == aInts[i])
            bIsIn = true;
    }

    return bIsIn;
}

/*
    Check if `nDay` is a weekday (Monday-Friday)
    @param nDay in-game day count
    @return `true` if `nDay` (converted to the day of the week) is a weekday
*/
int
isWeekday (int nDay)
{
    return isInRange(toDayOfWeek(nDay), MONDAY, FRIDAY);
}

/*
    Check if `nAction` is a hangout action (i.e. confidant interaction)
    @param nAction action ID
    @return `true` if `nAction` is a confidant action
*/
int
isConfAction (int nAction)
{
    return isInRange(nAction, HANGOUT_SOJIRO, HANGOUT_HARU_BBB);
}

/*
    Return true or false based on whether or not `nAction` is an action that
    can only be performed in the evening.
    @param nAction action id
    @return `true` if `nAction` can only be selected in the evening.
    (Note that confidant actions are handled by the isConfActiveNow() function)
*/
int
isEveningAction (int nAction)
{
    return (nAction == DO_WARM_BATH || nAction == DO_BBB_CHALLENGE);
}

/*
    Check if `nItem` is a permanent upgrade item, i.e., check if `nItem` is an
    item that will permanently stay in your inventory once it has been bought.
    @param nItem item ID
    @return `true` if `nItem` is a permanent upgrade item
*/
int
isUpgradeItem (int nItem)
{
    return isInRange(nItem, DVD_PLAYER, BRAVERY_DOG);
}

/*
    Check if `nItem` is an gift item
    @param nItem item ID
    @return `true` if `nItem` is a gift item
*/
int 
isGiftItem (int nItem)
{
    return isInRange(nItem, BBB_PLUSH, PERSONALIZED_PEN);
}

/*
    Check if `nItem` is an boost item
    @param nItem item ID
    @return `true` if `nItem` is a boost item
*/
int
isBoostItem (int nItem)
{
    return isInRange(nItem, HERBAL_SUPPLEMENT, GREEN_TEA_SUPPLEMENT);
}

/* ------------------------------------- */
/*   III. Miscellaneous Game Functions   */
/* ------------------------------------- */

/*
    Control the player location based on the input event and current location.
    @param nInput input event (0: North; 1: South; 2: East; 3: West)
    @param nDay in-game day counter
    @param nPeriod in-game period counter
    @param pLocation pointer to `nLocation` (player location)
*/
void
controlLocation (int nInput, int nDay, int nPeriod, int *pLocation)
{
    /*
    `aMap` is a 2D array where each location corresponds to a 4-element array
    consisting of an adjacent location to the NORTH, SOUTH, EAST, and WEST
    of the location.
    */ 
    int aMap[AMOUNT_PLACES][4];
    for (int i = 0; i < AMOUNT_PLACES; i++)
        set(aMap[i], 4, NONE);

    aMap[LEBLANC_CAFE][MAP_SOUTH]     = BACK_ALLEY;
    aMap[BACK_ALLEY][MAP_NORTH]       = LEBLANC_CAFE;
    aMap[BACK_ALLEY][MAP_SOUTH]       = CLINIC;
    aMap[BACK_ALLEY][MAP_EAST]        = TRAIN_STATION;
    aMap[CLINIC][MAP_NORTH]           = BACK_ALLEY;
    aMap[TRAIN_STATION][MAP_NORTH]    = SHUJIN_ACADEMY;
    aMap[TRAIN_STATION][MAP_SOUTH]    = UNDERGROUND_MALL;
    aMap[TRAIN_STATION][MAP_EAST]     = SHIBUYA;
    aMap[TRAIN_STATION][MAP_WEST]     = BACK_ALLEY;
    aMap[UNDERGROUND_MALL][MAP_NORTH] = TRAIN_STATION;
    aMap[SHUJIN_ACADEMY][MAP_SOUTH]   = TRAIN_STATION;
    aMap[SHUJIN_ACADEMY][MAP_WEST]    = TRAIN_STATION;
    aMap[SHIBUYA][MAP_SOUTH]          = ARCADE;
    aMap[SHIBUYA][MAP_EAST]           = BIG_BANG_BURGER;
    aMap[SHIBUYA][MAP_WEST]           = TRAIN_STATION;
    aMap[BIG_BANG_BURGER][MAP_WEST]   = SHIBUYA;
    aMap[ARCADE][MAP_NORTH]           = SHIBUYA;

    int nDestination = aMap[*pLocation][nInput];
    int bIsShujinOpen = (isWeekday(nDay) && nPeriod == AFTERNOON);

    if (nDestination != NONE)
    {
        if (nDestination != SHUJIN_ACADEMY || bIsShujinOpen)
        {
            *pLocation = nDestination;
        }
        else
        {
            /*
            This shouldn't affect displayConfsHere() because no confidant is
            available in the TRAIN_STATION when SHUJIN_ACADEMY is closed
            */
            displayFooter(TEXT_SHUJIN_CLOSED "\n| " TEXT_ANYKEY);
            captureInput();
            displayFooter("");
        }
    }
}

/*
    Return true or false depending on the presence of `nConfidant`
    during `nPeriod` of `nDay` at `nLocation`.
    Precondition: `nLocation` is a location where an `nAction` exists
                  such `toConf(nAction) == nConfidant`, where `nConfidant` is an
                  unlocked confidant.
    @param nConfidant confidant ID
    @param nLocation location ID
    @param nDay in-game day counter
    @param nPeriod in-game period counter
    @return true or false depending on confidant's availability based on the
    parameters
*/
int
isConfActiveNow (int nConfidant, int nLocation, int nDay, int nPeriod)
{
    int bIsAvailable;
    int nDayOfWeek = toDayOfWeek(nDay);
    int bIsWeekday = isWeekday(nDay);
    switch (nConfidant)
    {
        case SOJIRO:
            bIsAvailable = nPeriod == EVENING &&
                           (!bIsWeekday || nDayOfWeek == WEDNESDAY);
            break;
        case RYUJI:
            bIsAvailable = nPeriod == AFTERNOON &&
                           ((nLocation == SHUJIN_ACADEMY && bIsWeekday) ||
                            (nLocation == ARCADE && nDayOfWeek == SATURDAY));
            break;
        case ANN:
        case MAKOTO:
        case YUSUKE:
            bIsAvailable = nPeriod == AFTERNOON && bIsWeekday;
            break;
        case FUTABA:
            bIsAvailable = nPeriod == AFTERNOON && bIsWeekday &&
                           nDayOfWeek != WEDNESDAY;
            break;
        case HARU:
            bIsAvailable = (nPeriod == AFTERNOON &&
                            nLocation == SHUJIN_ACADEMY && bIsWeekday) ||
                           (nPeriod == EVENING &&
                            nLocation == BIG_BANG_BURGER && !bIsWeekday);
            break;
        case TAE:
            bIsAvailable = (nDayOfWeek != SATURDAY &&
                            nPeriod == EVENING);
            break;
        case SADAYO:
            bIsAvailable = (nDayOfWeek != TUESDAY  && nDayOfWeek != WEDNESDAY &&
                            nDayOfWeek != SATURDAY && nPeriod == EVENING);
            break;
        case SUMIRE:
            bIsAvailable = (bIsWeekday && nDayOfWeek != TUESDAY &&
                            nDayOfWeek != THURSDAY &&
                            nPeriod == AFTERNOON);
            break;
        default:
            return false;
    }
    return bIsAvailable;
}

/*
    Check `aStatPts` and compare it with `aConfReqs`. When you reach the stat
    requirement for any locked confidant, turn them unlockable
    (i.e., `aConfPts[nConf] = -1 (UNLOCKABLE)`)
    @param aStatPts the player's stat points
    @param aConfPts the player's confidant relationship points
    @return For every locked confidant `nConf` that we've reached the
    requirements to unlock, set `aConfPts[nConf]` to `-1 (UNLOCKABLE)`
*/
void
checkConfReqs (int aStatPts[], int aConfPts[])
{
    int aConfReqs[AMOUNT_CONFIDANTS][AMOUNT_STATS] = {
                     /* KINDNESS        GUTS   KNOWLEDGE */
        /* SOJIRO */ {         0,          0,          0},
        /* RYUJI  */ {         0,          0,          0},
        /* ANN    */ {SOCIAL_LV1, SOCIAL_LV1,          0},
        /* YUSUKE */ {         0,          0, SOCIAL_LV1},
        /* MAKOTO */ {         0,          0, SOCIAL_LV2},
        /* FUTABA */ {SOCIAL_LV2,          0, SOCIAL_LV2},
        /* HARU   */ {SOCIAL_LV3,          0, SOCIAL_LV3},
        /* TAE    */ {SOCIAL_LV3, SOCIAL_LV3,          0},
        /* SADAYO */ {         0, SOCIAL_LV3, SOCIAL_LV3},
        /* SUMIRE */ {SOCIAL_LV3, SOCIAL_LV3, SOCIAL_LV3},
    };
    int nUnlockableConfs = 0;
    int bUnlockable;
    int nConfidant;
    int nStat;
    for (nConfidant = SOJIRO; nConfidant < AMOUNT_CONFIDANTS; nConfidant++)
    {
        if (aConfPts[nConfidant] == LOCKED)
        {
            bUnlockable = true;
            for (nStat = 0; nStat < AMOUNT_STATS; nStat++)
            {
                if (aStatPts[nStat] < aConfReqs[nConfidant][nStat])
                    bUnlockable = false;
            }
            if (bUnlockable)
            {
                aConfPts[nConfidant] = UNLOCKABLE;
                nUnlockableConfs++;
            }
        }
    }
}

/*
    Get the confidants in the current `nLocation` and store the result in
    `aConfsHere`. There will always be at most 3 confidants in a location.
    @param nLocation the place to check for confidants
    @param aConfsHere the array to store the result in
    @return `aConfsHere` will get updated to include at most 3 confidant IDs
    based on the presence of confidants in the location specified
*/
void
getConfsHere (int nLocation, int aConfsHere[MAX_CONFS_IN_LOCATION])
{
    int aActionsHere[ACTION_MENU_LIMIT];
    set(aConfsHere, MAX_CONFS_IN_LOCATION, NONE);
    int nConfCount;
    int i;
    initActions(nLocation, aActionsHere);

    i = 0;
    nConfCount = 0;
    while (nConfCount < MAX_CONFS_IN_LOCATION && i < ACTION_MENU_LIMIT)
    {
        if (isConfAction(aActionsHere[i]))
        {
            aConfsHere[nConfCount++] = toConf(aActionsHere[i]);
        }
        i++;
    }
}

/*
Loop through every confidant in `nLocation` and trigger their
unlock event if they are unlockable. Returns true if a confidant was unlocked.
*/
int
tryUnlockEvent (int nLocation, int nDay, int nPeriod, int aConfPts[])
{
    // Check for confidants that we can supposedly interact with.
    int aConfsHere[MAX_CONFS_IN_LOCATION];
    int nConfidant;
    int bUnlocked = false;
    int i;
    getConfsHere(nLocation, aConfsHere);
    for (i = 0; i < MAX_CONFS_IN_LOCATION; i++)
    {
        nConfidant = aConfsHere[i];
        if (aConfPts[nConfidant] == UNLOCKABLE
            && isConfActiveNow(nConfidant, nLocation, nDay, nPeriod))
        {
            /*
            Despite being able to be interacted with in BIG_BANG_BURGER,
            HARU can be unlocked only in SHUJIN_ACADEMY.
            (Given that RYUJI will always be automatically unlocked by
            Day 2, there is no need to check for him)
            */ 
            if (nConfidant != HARU || nLocation == SHUJIN_ACADEMY)
            {
                triggerEvent(nConfidant, UNLOCK_EVENT);
                aConfPts[nConfidant] = CONF_LV1;
                bUnlocked = true;
            }
        }
    }
    return bUnlocked;
}

/*
Get the valid actions that the player can perform in a given `nLocation` at
a certain `nDay` and `nPeriod` with the current `aConfPts`.
*/
void
getActions (int nLocation, int nDay, int nPeriod,
            int aConfPts[], int aItems[], int aActions[])
{
    int aActionsHere[ACTION_MENU_LIMIT];
    int nValidActions = 0;
    int nAction;
    int nConfidant;
    int i;
    int bValidAction;
    initActions(nLocation, aActionsHere);
    set(aActions, ACTION_MENU_LIMIT, NONE);
    i = 0;
    do
    {
        bValidAction = false;
        nAction = aActionsHere[i];
        if (isConfAction(nAction))
        {
            nConfidant = toConf(nAction);
            if (aConfPts[nConfidant] >= CONF_LV1 &&
                isConfActiveNow(nConfidant, nLocation, nDay, nPeriod))
            {
                bValidAction = true;
            }
        }
        else if ((isEveningAction(nAction) && nPeriod != EVENING) ||
            (nAction == DO_WATCH_DVD && aItems[DVD_PLAYER] == NONE))
        {
            bValidAction = false;
        }
        else
        {
            bValidAction = true;
        }

        if (bValidAction)
            aActions[nValidActions++] = nAction;
        i++;
    } while (aActionsHere[i] != NONE && i < ACTION_MENU_LIMIT);
}
