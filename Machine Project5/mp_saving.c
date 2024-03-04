/*
    Saving, loading, and autosaving
    TODO: Save and load confidant gift status
*/

/*
    Save a file and store the details into the file at save `nSaveNum`.
    @param nSaveNum save number
    @param nLocation pointer to player's location
    @param nDay pointer to the current day
    @param nPeriod pointer to the current period
    @param nYen pointer to yen
    @param nBBBLv pointer to the current BBB challenge level
    @param nLentMoney pointer to Yusuke's "owing us" state
    @param aConfPts confidant points
    @param aStatPts social stat points
    @param aItems inventory
    @param aItemsBoughtToday items the player has bought today (or
    upgrade or gift items the player has bought so far)
    @param aConfGifted whether or not any confidants have been gifted items
    this plathrough
*/
void
save (int nSaveNum, int nLocation, int nDay, int nPeriod, int nYen,
      int nBBBLv, int bLentMoney, int aConfPts[], int aStatPts[],
      int aItems[], int aItemsBoughtToday[], int aConfGifted[])
{
    FILE *pFile;
    char sFileName[CHR_LIMIT];

    int i;
    sprintf(sFileName, "%d.p5tb", nSaveNum);
    pFile = fopen(sFileName, "wt");
    fprintf(pFile, "%d ", nLocation);
    fprintf(pFile, "%d ", nDay);
    fprintf(pFile, "%d ", nPeriod);
    fprintf(pFile, "%d ", nYen);
    fprintf(pFile, "%d ", nBBBLv);
    fprintf(pFile, "%d\n", bLentMoney);
    for (i = 0; i < AMOUNT_CONFIDANTS; i++)
    {
        fprintf(pFile, "%d ", aConfPts[i]);
    }
    fprintf(pFile, "\n");
    for (i = 0; i < AMOUNT_STATS; i++)
    {
        fprintf(pFile, "%d ", aStatPts[i]);
    }
    fprintf(pFile, "\n");
    for (i = 0; i < ITEM_MENU_LIMIT; i++)
    {
        fprintf(pFile, "%d ", aItems[i]);
    }
    fprintf(pFile, "\n");
    for (i = 0; i < AMOUNT_ITEMS; i++)
    {
        fprintf(pFile, "%d ", aItemsBoughtToday[i]);
    }
    fprintf(pFile, "\n");
    for (i = 0; i < AMOUNT_CONFIDANTS; i++)
    {
        fprintf(pFile, "%d ", aConfGifted[i]);
    }
    fclose(pFile);
}

/*
    Load a file and store the details into the player detail parameters.
    @param nSaveNum save number
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
*/
int
load (int nSaveNum, int *pLocation, int *pDay, int *pPeriod, int *pYen,
      int *pBBBLv, int *pLentMoney, int aConfPts[], int aStatPts[],
      int aItems[], int aItemsBoughtToday[], int aConfGifted[])
{
    int i;
    int bSuccess;
    char sFileName[CHR_LIMIT];
    FILE *pFile;

    sprintf(sFileName, "%d.p5tb", nSaveNum);
    pFile = fopen(sFileName, "rt");
    if (pFile != NULL)
    {
        fscanf(pFile, "%d", pLocation);
        fscanf(pFile, "%d", pDay);
        fscanf(pFile, "%d", pPeriod);
        fscanf(pFile, "%d", pYen);
        fscanf(pFile, "%d", pBBBLv);
        fscanf(pFile, "%d", pLentMoney);
        for (i = 0; i < AMOUNT_CONFIDANTS; i++)
        {
            fscanf(pFile, "%d", &aConfPts[i]);
        }
        for (i = 0; i < AMOUNT_STATS; i++)
        {
            fscanf(pFile, "%d", &aStatPts[i]);
        }
        for (i = 0; i < ITEM_MENU_LIMIT; i++)
        {
            fscanf(pFile, "%d", &aItems[i]);
        }
        for (i = 0; i < AMOUNT_ITEMS; i++)
        {
            fscanf(pFile, "%d", &aItemsBoughtToday[i]);
        }
        for (i = 0; i < AMOUNT_CONFIDANTS; i++)
        {
            fscanf(pFile, "%d", &aConfGifted[i]);
        }
        fclose(pFile);
        bSuccess = true;
    }
    else
    {
        bSuccess = false;
    }
    return bSuccess;
}