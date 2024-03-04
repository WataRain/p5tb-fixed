/*
These functions represent the game actions such as:
1. Confidant actions (hanging out with Futaba)
2. Shop actions (buying something from the Second Hand Shoppe)
3. Stat boosting actions (studying in LeBlanc Cafe)
*/

/*
    Attempt to pay `nVal`. Returns true if successful, false otherwise
    @param nVal the amount to pay
    @param pYen pointer to `nYen`, the money currently on hand
    @return `true` or `false` depending on the player being able to pay
    for the item. If the player can pay for the item, then `*pYen is
    subtracted with `nVal` as well.
*/
int
pay (int nVal, int *pYen)
{
    int bSuccess = false;
    char sResult[CHR_LIMIT];
    if (*pYen >= nVal)
    {
        *pYen -= nVal;
        sprintf(sResult, "You paid Y%d!", nVal);
        bSuccess = true;
    }
    else
    {
        sprintf(sResult, BACK_RED TEXT_NO_YEN " " TEXT_ANYKEY COLOR_RESET);
    }
    displayFooter(sResult);
    captureInput();
    return bSuccess;
}

/*
    Increase `*pYen` by `nVal` and display a notification.
    @param nVal The amount to increase `*pYen` by
    @param pYen Pointer to `nYen`
    @param sFlavor Flavor text
*/
void
earn (int nVal, int *pYen)
{
    printf("| You earned Y%d!\n", nVal);
    *pYen += nVal;
}

/*
    If `nItem` is the active BOOST item in the inventory `aItems`, then
    activate a boost bonus and make it disappear from the inventory.
    @param aItems the inventory
    @param nItem the item ID which will activate the bonus and get consumed
    @return `1` if `nItem1` is the current boost item in `aItems`, `0` otherwise
*/
int
boostBonus (int aItems[], int nItem)
{
    int nBonusAdd = 0;
    if (aItems[BOOST] == nItem)
    {
        nBonusAdd++;
        aItems[BOOST] = NONE;
        printf("\n| You used the ");
        displayItem(nItem);
        printf("!\n");
    }
    return nBonusAdd;
}

/* --- Confidant Actions --- */

/*
    Add `nVal` confidant points to `aConfPts[nConfidant]`.
    @param nConfidant the confidant id
    @param nVal value to add confidant points with
    @param aConfPts array of confidant points
*/
void
addConfPts (int nConfidant, int nVal, int aConfPts[])
{
    // Player has not triggered Confidant's MAX EVENT, add Confidant Points
    if (aConfPts[nConfidant] != CONF_MAX)
    {
        aConfPts[nConfidant] += nVal;
        printf("| You gained %d confidant points with ", nVal);
        displayConf(nConfidant);
        if (aConfPts[nConfidant] >= CONF_MAX)
        {
            aConfPts[nConfidant] = CONF_LV3;
        }
    }
    else
    {
        // Player has already triggered Confidant's MAX EVENT
        printf("| You've already maxed out your points for this confidant.\n");
    }
    printf("\n");
}

/*
    Spend time with `nConfidant`, increasing relationship points with them.
    @param nConfidant confidant ID
    @param aConfPts relationship points with every confidant
*/
void
hangout (int nConfidant, int aConfPts[], int aItems[])
{
    int nBonus = 1;
    displayConfHangout(nConfidant);

    // Confidant is Level 3: Trigger Confidant's MAX EVENT
    if (aConfPts[nConfidant] == CONF_LV3)
    {
        triggerEvent(nConfidant, MAX_EVENT);
        aConfPts[nConfidant] = CONF_MAX;
    }
    else if (aConfPts[nConfidant] != CONF_MAX)
    {
        nBonus += boostBonus(aItems, GREEN_TEA_SUPPLEMENT);
        addConfPts(nConfidant, 2 * nBonus, aConfPts);
    }
    // TODO:
    // "Spending time with some confidants can randomly give points
    // for stats as well"
}

/* --- Job Action --- */

/*
    Earn Yen for jobs. Each job earns around Y400-800 multiplied by 1 plus the
    stat level of a certain stat.
    @param aStatPts[] array representing the stat points of a player
    @param nJob action ID representing a job
    @param *pYen pointer to `nYen`
*/
void
jobEarn (int aStatPts[], int nJob, int *pYen)
{
    int nJobStat = nJob - JOB_FLOWER;
    earn(randInt(400, 800) * (toStatLv(aStatPts[nJobStat]) + 1), pYen);
}

/* --- Shop Actions --- */

/*
    Return true if the player already has a gift. Also alerts the player if
    the player has a gift.
    @param aItems inventory
    @return `true` if the player already has a gift, `false` otherwise
*/
int
alreadyHasGift (int aItems[])
{
    int bAlreadyHasGift = false;
    if (aItems[GIFT] != NONE)
    {
        bAlreadyHasGift = true;
        displayFooter("You already have a gift item in your storage!"
                      "\n| Give a confidant that gift before buying another!"
                      "\n| " TEXT_ANYKEY);
        captureInput();
    }
    return bAlreadyHasGift;
}

/*
    Shop at `nShop`.
    @param nShop action ID representing a shop action
    @param nTakemiPts confidant points with Takemi. GREEN_TEA_SUPPLEMENT can be
    purchased if `nTakemiPts >= CONF_LV1`.
    @param pYen pointer to Yen
    @param aItems inventory
    @param aItemsBoughtToday array representing items already bought today.
    Note that aItemsBoughtToday does not reset for gift items nor upgrade items,
    as they can only be bought once in a playthrough.
*/
void
shopAt (int nShop, int nTakemiPts, int *pYen, int aItems[ITEM_MENU_LIMIT],
        int aItemsBoughtToday[AMOUNT_ITEMS])
{
    int i;
    int nItem;
    int nPrice;
    int nChoice; // 0 for quit, 1 and above to buy an item
    int bHasPurchased = false; 
    int aShopItems[3];
    int aShopPrices[3];
    // Initialize price data
    int aPriceData[AMOUNT_ITEMS];
    aPriceData[DVD_PLAYER]           = 5000;
    aPriceData[MUSIC_PLAYER]         = 5000;
    aPriceData[ETIQUETTE_101]        = 1000;
    aPriceData[MYSTERY_CIVILIZATION] = 1000;
    aPriceData[BRAVERY_DOG]          = 1000;
    aPriceData[BBB_PLUSH]            = 1000;
    aPriceData[DESK_CLOCK]           = 2000;
    aPriceData[EUCALYPTUS_EXTRACT]   = 2500;
    aPriceData[PERFUME]              = 2000;
    aPriceData[PERSONALIZED_PEN]     = 1500;
    aPriceData[HERBAL_SUPPLEMENT]    = 2000;
    aPriceData[PORK_TONKOTSU_BOWL]   = 1500;
    aPriceData[CHICKEN_KATSU_BOWL]   = 1500;
    aPriceData[BBB_COMBO]            = 1000;
    aPriceData[GREEN_TEA_SUPPLEMENT] = 1500;
    aPriceData[HERBAL_ESSENCE]       = 3000;
    // Initialize shop data - set aShopItems with the items from nShop
    int aShopData[][3] = {
        // Second Hand Shoppe
        {MUSIC_PLAYER, DVD_PLAYER, DESK_CLOCK},
        // Vitamin Shop
        {HERBAL_SUPPLEMENT, EUCALYPTUS_EXTRACT, GREEN_TEA_SUPPLEMENT},
        // Tonkotsu King
        {PORK_TONKOTSU_BOWL, CHICKEN_KATSU_BOWL, NONE},
        // Gift Shop
        {PERFUME, PERSONALIZED_PEN, HERBAL_ESSENCE},
        // DVD Shop
        {ETIQUETTE_101, MYSTERY_CIVILIZATION, BRAVERY_DOG},
        // Big Bang Burger
        {BBB_COMBO, BBB_PLUSH, NONE}
    };
    for (i = 0; i < 3; i++)
        aShopItems[i] = aShopData[nShop][i];

    char sItemName[CHR_LIMIT];
    char aShopItemListings[4][CHR_LIMIT];
    char sItemListing[CHR_LIMIT];

    strcpy(aShopItemListings[0], "Exit");

    // Initialize shop items
    for (i = 0; i < 3; i++)
    {
        nItem = aShopItems[i];
        copyItemName(sItemName, nItem);
        // If nItem is something that is not in the player's inventory
        // and the item has not been bought today
        // & (the item is not GREEN_TEA_SUPPLEMENT or Takemi has been unlocked)
        if (nItem != NONE && !in(nItem, aItems, ITEM_MENU_LIMIT) &&
            aItemsBoughtToday[nItem] == false &&
            (nItem != GREEN_TEA_SUPPLEMENT || nTakemiPts >= CONF_LV1))
        {
            nPrice = aPriceData[nItem];
            sprintf(sItemListing, "%s - Y%d", sItemName, nPrice);
            aShopPrices[i] = nPrice;
            strcpy(aShopItemListings[i+1], sItemListing);
        }
        else
        {
            strcpy(aShopItemListings[i+1], "");
        }
    }

    do
    {
        // Shop menu
        displayShopName(nShop);
        nChoice = listMenu(aShopItemListings, 4, 3, FOOTER_Y + 1);

        // Process purchase
        if (nChoice)
        {
            nItem = aShopItems[nChoice-1];
            nPrice = aShopPrices[nChoice-1];
            displayItemDesc(nItem);
            locate(3, FOOTER_Y + 4);
            printf("It costs Y%d. Want to buy?", nPrice);
            if (askYesNo(3, FOOTER_Y + 5) &&
                (!isGiftItem(nItem) || !alreadyHasGift(aItems)) &&
                pay(nPrice, pYen))
            {
                bHasPurchased = true;
                displayFooter("You purchased");
                printf("| ");
                displayItem(nItem);
                printf("!");
                aItemsBoughtToday[nItem] = true;
                if (isUpgradeItem(nItem))
                {
                    aItems[nItem] = nItem;
                }
                else if (isGiftItem(nItem))
                {
                    aItems[GIFT] = nItem;
                }
                else if (isBoostItem(nItem))
                {
                    aItems[BOOST] = nItem;
                }
                strcpy(aShopItemListings[nChoice], "");
            }
        }
    // until a player purchases or exits (nChoice=0 == QUIT)
    } while (!bHasPurchased && nChoice); 
    displayFooter("");
}

/* --- Stat Boosting Actions --- */

/*
    Add `nVal` points to `aStatPts[nStat]`
    @param nStat the stat to add to (`KINDNESS`, `GUTS`, `KNOWLEDGE`)
    @param nVal the value to add
    @param aStatPts array with the stat points for each `nStat`
*/
void
addStatPts (int nStat, int nVal, int aStatPts[])
{
    aStatPts[nStat] += nVal;
    if (aStatPts[nStat] >= SOCIAL_LV3)
    {
        aStatPts[nStat] = SOCIAL_LV3;
        printf("| You've reached the max level for ");
        displayStat(nStat);
        printf("!\n");
    }
    else
    {
        printf("| Your ");
        displayStat(nStat);
        printf(" increased by %d stat point%s!\n", nVal,
               (nVal != 1) ? "s" : "");
    }
}

/*
    Perform a generic stat boost action.
    The action will add `nVal` points to the specified `nStat` in `aStatPts`.
    This value will be doubled if nBoostItem` (or `HERBAL_SUPPLEMENT`, the
    generic stat gain doubler item) is in the inventory `aItems`. Finally,
    display the flavor text `sFlavor` in the footer.
    @param aStatPts social stat points
    @param nStat stat to raise
    @param nVal how much the stat should raise
    @param aItems inventory
    @param nBoostItem item that would double `nVal`
    @param sFlavor string for flavor text
*/
void
doStatBoost (int aStatPts[], int nStat, int nVal, int aItems[], int nBoostItem,
             char sFlavor[])
{
    int nBonus = 1;
    displayFooter(sFlavor);
    nBonus += boostBonus(aItems, HERBAL_SUPPLEMENT);
    nBonus += boostBonus(aItems, nBoostItem);
    addStatPts(nStat, nVal * nBonus, aStatPts);
}

/*
    Perform a paid stat boost action.
    If `*pYen >= nCost`, then `*pYen -= nCost` and the action will add `nVal`
    points to the specified `nStat` in `aStatPts`.
    This value will be doubled if `nBoostItem` (or `HERBAL_SUPPLEMENT`, the
    generic stat gain doubler item) is in the inventory `aItems`. Finally,
    display the flavor text `sFlavor` in the footer.
    @param aStatPts social stat points
    @param nStat stat to raise
    @param nVal how much the stat should raise
    @param pYen pointer to Yen
    @param nCost cost of action
    @param aItems inventory
    @param nBoostItem item that would double `nVal`
    @param sFlavor string for flavor text
    @return `true` if the player was able to successfully pay for the action,
    `false` otherwise
*/
int
doPaidStatBoost (int aStatPts[], int nStat, int nVal, int *pYen, int nCost,
                 int aItems[], int nBoostItem, char sFlavor[])
{
    int bActSuccess = false;
    if (pay(nCost, pYen))
    {
        bActSuccess = true;
        doStatBoost(aStatPts, nStat, nVal, aItems, nBoostItem, sFlavor);
    }
    return bActSuccess;
}

/*
    Study at LeBlanc Cafe.
    @param aStatPts social stat points
    @param aItems inventory
*/
void
doStudyLeBlanc (int aStatPts[], int aItems[])
{
    int nBonus = 1;
    displayFooter(TEXT_STUDY_LEBLANC);
    nBonus += boostBonus(aItems, HERBAL_SUPPLEMENT);
    nBonus += boostBonus(aItems, CHICKEN_KATSU_BOWL);
    if (in(MUSIC_PLAYER, aItems, ITEM_MENU_LIMIT) && chance(75))
    {
        printf("| " TEXT_STUDY_LEBLANC2 "\n");
        addStatPts(KNOWLEDGE, 2 * nBonus, aStatPts);
    }
    else
    {
        addStatPts(KNOWLEDGE, 1 * nBonus, aStatPts);
    }
}

/*
    Clean the blackboard.
    @param aStatPts social stat points
    @param aItems inventory
*/
void
doClean (int aStatPts[], int aItems[])
{
    int nFlatBonus = 1;
    int nKnowBonus = 1;

    displayFooter(TEXT_CLEAN);
    switch (randInt(1, 4))
    {
        case 1:
            nFlatBonus += boostBonus(aItems, HERBAL_SUPPLEMENT);
            addStatPts(KINDNESS, 2 * nFlatBonus, aStatPts);
            break;
        case 2:
            nFlatBonus += boostBonus(aItems, HERBAL_SUPPLEMENT);
            nKnowBonus += boostBonus(aItems, CHICKEN_KATSU_BOWL);
            addStatPts(KNOWLEDGE, 1 * (nFlatBonus + nKnowBonus - 1), aStatPts);
            addStatPts(KINDNESS, 1 * nFlatBonus, aStatPts);
            break;
        case 3:
            nFlatBonus += boostBonus(aItems, HERBAL_SUPPLEMENT);
            nKnowBonus += boostBonus(aItems, CHICKEN_KATSU_BOWL);
            addStatPts(KNOWLEDGE, 2 * (nFlatBonus + nKnowBonus - 1), aStatPts);
            break;
        case 4:
            printf(TEXT_NOTHING);
            break;
    }
}

/*
    Watch a DVD (if you have a DVD Player and any DVD)
    @param aStatPts social stat points
    @param aItems inventory
*/
int
doWatchDVD (int aStatPts[], int aItems[])
{
    char aDVDListing[4][CHR_LIMIT];
    int bActSuccess = false;
    int bHasDVD = false;
    int nBonus = 0;
    int nDVD, i;
    int nStat;

    strcpy(aDVDListing[0], "Cancel");
    for (nDVD = ETIQUETTE_101; nDVD <= BRAVERY_DOG; nDVD++)
    {
        i = nDVD - ETIQUETTE_101 + 1;
        if (aItems[nDVD] != NONE)
        {
            copyItemName(aDVDListing[i], nDVD);
            bHasDVD = true;
        }
        else
        {
            strcpy(aDVDListing[i], "");
        }
    }
    if (bHasDVD)
    {
        displayFooter(TEXT_CHOOSE_DVD);
        bActSuccess = true;
        switch (listMenu(aDVDListing, 4, 3, FOOTER_Y +1))
        {
            case 1: // Etiquette 101
                nStat = KINDNESS;
                displayFooter(TEXT_WATCH_ETIQUETTE);
                break;
            case 2: // Mystery
                nStat = KNOWLEDGE;
                displayFooter(TEXT_WATCH_MYSTERY);
                break;
            case 3: // Bravery
                nStat = GUTS;
                displayFooter(TEXT_WATCH_BRAVERY);
                break;
            default:
                bActSuccess = false;
                break;
        }
        if (bActSuccess)
        {
            nBonus += boostBonus(aItems, BBB_COMBO);
            addStatPts(nStat, 2 + nBonus, aStatPts);
        }
    }
    else
    {
        displayFooter(TEXT_NO_DVD "\n| " TEXT_ANYKEY);
        captureInput();
    }

    return bActSuccess;
}

/*
    Attempt to take a warm bath
    @param aStatPts player social stat points
    @param pYen pointer to yen
    @param aItems inventory
    @return `true` if the action was successful, `false` otherwise
*/
int
doWarmBath (int aStatPts[], int *pYen, int aItems[])
{
    int nStat = randInt(KINDNESS, KNOWLEDGE);
    int nBonus = 1;
    int bActionSuccessful = false;
    displayFooter("");
    if (pay(500, pYen))
    {
        bActionSuccessful = true;
        displayFooter(TEXT_WARM_BATH);
        nBonus += boostBonus(aItems, HERBAL_SUPPLEMENT);
        switch (nStat)
        {
            case KINDNESS:
                /* HERBAL_ESSENCE only works when tending to plants
                   so no boost bonus here */
                break;
            case GUTS:
                nBonus += boostBonus(aItems, PORK_TONKOTSU_BOWL);
                break;
            case KNOWLEDGE:
                nBonus += boostBonus(aItems, CHICKEN_KATSU_BOWL);
                break;
        }
        addStatPts(nStat, randInt(1, 2) * nBonus, aStatPts);
    }
    return bActionSuccessful;
}

/*
    Perform the BBB Challenge.
    @param aStatPts array representing stat points
    @param pYen pointer to yen
    @param aItems inventory
    @param pBBBLv pointer to BBB challenge level
    @return `true` if time should pass; `false` otherwise
*/
int
doChallenge (int aStatPts[], int *pYen, int aItems[], int *pBBBLv)
{
    int bActSuccess = false;
    int bWon;
    int nPts;
    int nStat;
    char sClearTxt[CHR_LIMIT];

    displayFooter("");
    if (aItems[BOOST] != NONE)
    {
        displayFooter(TEXT_CHALLENGE_FULL "\n| " TEXT_ANYKEY);
        captureInput();
    }
    else if (*pBBBLv > 3)
    {
        displayFooter(TEXT_CHALLENGE_OVER "\n| " TEXT_ANYKEY);
        captureInput();
    }
    else if (pay(1500, pYen))
    {
        bActSuccess = true;
        bWon = false;
        sprintf(sClearTxt, TEXT_CHALLENGE "%d!", (*pBBBLv));
        switch (*pBBBLv)
        {
            case 1:
                if (chance(40))
                {
                    bWon = true;
                    nPts = 1;
                }
                break;
            case 2:
                if (minStatLv(aStatPts) >= 1 && chance(50))
                {
                    bWon = true;
                    nPts = 3;
                }
                break;
            case 3:
                if (minStatLv(aStatPts) >= 2 && chance(50))
                {
                    bWon = true;
                    nPts = 4;
                }
                break;
        }
        if (bWon)
        {
            displayFooter(sClearTxt);
            // Increase stat points for all social stats
            for (nStat = KINDNESS; nStat < AMOUNT_STATS; nStat++)
            {
                addStatPts(nStat, nPts, aStatPts);
            }
            (*pBBBLv)++; // BBB challenge level up
        }
        else
            printf("| Unfortunately, you lost the challenge...\n");
    }
    return bActSuccess;
}

