// Bools
#define false 0
#define true 1

// Keyboard
#define ENTER 13
#define ARROW_START -32
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

// UI
#define ACTION_MENU_LIMIT 8
#define ITEM_MENU_LIMIT 7
#define FOOTER_Y 26
#define UI_RIGHT_X 76

/*
Inventory indices (inventory has ITEM_MENU_LIMIT items)
The player is only allowed to have one boost item and one gift item at a time.
Here are their indices:
*/
#define GIFT 5
#define BOOST 6
#define MAX_CONFS_IN_LOCATION 4
// Each string variable can have at most CHR_LIMIT chars
#define CHR_LIMIT 256

/* -- Vars -- */

#define DAYS 60
#define NONE -1

/* -- Colors -- */

#define COLOR_RESET "\e[0m"
#define FORE_BLACK "\x1B[30m"
#define FORE_RED "\x1B[31m"
#define FORE_YELLOW "\x1B[33m"
#define FORE_BLUE "\x1B[34m"
#define BACK_WHITE "\x1B[47m"
#define BACK_GRAY "\x1B[100m"
#define BACK_RED "\x1B[41m"
#define BACK_GREEN "\x1B[42m"
#define BACK_YELLOW "\x1B[43m"
#define BACK_BLUE "\x1B[44m"
#define BLACK_ON_WHITE FORE_BLACK BACK_WHITE

/* -- Text -- */

#define TEXT_HELP                                                            \
    "[WASD] Move around the map [UP/DOWN] Select from menu [ENTER] Confirm " \
    "[T] Toggle stat view [R] Redraw screen"
#define TEXT_SHUJIN_CLOSED \
    "Sorry, but Shujin Academy is closed at this time."
#define TEXT_NO_YEN \
    "You don't have enough Yen to do that!"
#define TEXT_ANYKEY \
    "Press any key to continue"
#define TEXT_BOOST_WASTED \
    "You weren't able to use your boost item."
#define TEXT_GAVE_CONF_GIFT_ALREADY \
    "You already gave that confidant a gift; you can't give them another!"
#define TEXT_MAXOUT \
    "You maxed out your confidant relationship points!" /* -- Confidants -- */

#define TEXT_FLAVOR_SOJIRO \
    "Sojiro greets you and says hi.\n"
#define TEXT_FLAVOR_RYUJI_SHUJIN \
    "Ryuji is training in the gym. He sees you and waves hi!\n"
#define TEXT_FLAVOR_RYUJI_ARCADE \
    "Ryuji runs towards you as he waves hi!\n"
#define TEXT_FLAVOR_ANN \
    "Ann waves at you from afar.\n"
#define TEXT_FLAVOR_YUSUKE \
    "Yusuke observes you, and then greets you.\n"
#define TEXT_FLAVOR_MAKOTO \
    "Makoto can be seen in the library.\n"
#define TEXT_FLAVOR_FUTABA \
    "Futaba is playing some video game.\n"
#define TEXT_FLAVOR_HARU_SHUJIN \
    "Haru is on the rooftop tending to plants.\n"
#define TEXT_FLAVOR_HARU_BBB \
    "Haru is tending to the Big Bang Burger.\n"
#define TEXT_FLAVOR_TAE \
    "Takemi looks relaxed in her chair.\n"
#define TEXT_FLAVOR_SADAYO \
    "Kawakami is available tonight. You think about calling her.\n"
#define TEXT_FLAVOR_SUMIRE \
    "Sumire is training in the gym too!\n"

#define TEXT_YUSUKE_ASK                                       \
    "| Yusuke: By the way, Ren, would you be so kind as to\n" \
    "|         lend me Y300 so I could ride the trains home?"
#define TEXT_YUSUKE_THANKS                                            \
    "| Yusuke: Before I depart, Ren, here's the Yen I owe you from\n" \
    "|         the last time we met. Thank you very much."

/* -- Action Results -- */

#define TEXT_J_FLOWER                                          \
    "It is said that plants are attracted to kind people.\n| " \
    "The same can be said for people, but you know that."
#define TEXT_J_GYUDON                                                          \
    "Have you got the guts? I hope you do, because you're gonna need some\n| " \
    "to work at the gyudon store!"
#define TEXT_J_CONVEN                                         \
    "Working hard at the convenience store is a job that\n| " \
    "smart people really excel at."
#define TEXT_STUDY_LEBLANC \
    "You studied at LeBlanc Cafe!"
#define TEXT_STUDY_LEBLANC2 \
    "The Music Player enhanced your studying!"
#define TEXT_CHOOSE_DVD \
    "Choose a DVD to watch!"
#define TEXT_NO_DVD \
    "You don't have any DVDs! Buy some at the shop!"
#define TEXT_WARM_BATH \
    "You took a warm bath. It was really refreshing!"
#define TEXT_TRAIN \
    "You trained hard in the Shujin Academy Gym!"
#define TEXT_LIBRARY \
    "You studied at the library."
#define TEXT_PLANTS \
    "You tended to the plants."
#define TEXT_CLEAN \
    "You cleaned the blackboard."
#define TEXT_NOTHING \
    "But nothing happened!"
#define TEXT_CAFE \
    "You relaxed at the nearby cafe."
#define TEXT_FITNESS \
    "You trained hard at the nearby fitness center!"
#define TEXT_CHALLENGE \
    "You cleared the Big Bang Burger Challenge Lv. "
#define TEXT_CHALLENGE_OVER \
    "You cleared all the levels; you can't take the BBB Challenge anymore!\n"
#define TEXT_CHALLENGE_FULL \
    "You are too full to take the BBB Challenge!"
#define TEXT_RHYTHM \
    "You played a rhythm game! You're a pro at this!"
#define TEXT_ZOMBIE \
    "You played a zombie shooter game! It was scary."

#define TEXT_WATCH_ETIQUETTE \
    "\n| You watched Etiquette 101! Very prim and proper!\n"
#define TEXT_WATCH_MYSTERY \
    "\n| Mystery of the Ancient Civilization! How mysterious, how ancient...\n"
#define TEXT_WATCH_BRAVERY \
    "\n| Bravery the Frightened Dog made you braver than the dog.\n"

/* -- Item Descriptions -- */

#define TEXT_MAY_GIFT "May make a nice gift."

#define DESC_BOOST_END1 \
    "\n| (Does not affect watching DVDs; effect wears off when advancing time)"
#define DESC_BOOST_END2 \
    "\n| Effect wears off when advancing time."
#define DESC_DVD_PLAYER \
    "Allows you to watch DVDs in LeBlanc Cafe (DVDs sold separately)."
#define DESC_MUSIC_PLAYER \
    "This music player sometimes helps you study better."
#define DESC_ETIQUETTE_101                                           \
    "An audiovisual presentation about a gentleman's etiquette.\n| " \
    "Watching him being so prim and proper rubs off on your kindness."
#define DESC_MYSTERY_CIVILIZATION                                  \
    "A documentary on a mysterious civilization. The insights\n| " \
    "provided by the narrator gives you knowledge."
#define DESC_BRAVERY_DOG                                                        \
    "\"We interrupt this program to bring you 'Bravery the Frightened Dog'\n| " \
    "show, starring Bravery, the frightened dog!\" Gives courage."
#define DESC_BBB_PLUSH \
    "A plushy of the Big Bang Burger mascot with some big eyes.\n| " TEXT_MAY_GIFT
#define DESC_DESK_CLOCK                                              \
    "This desk clock tells time. Gifting this to a friend would\n| " \
    "show how much you value the time you spend with them!\n| " TEXT_MAY_GIFT
#define DESC_EUCALYPTUS_EXTRACT \
    "Medicinal properties of the eucalyptus oil have healing benefits.\n| " TEXT_MAY_GIFT
#define DESC_PERFUME \
    "There's a subtle fragrance to this perfume. " TEXT_MAY_GIFT
#define DESC_PERSONALIZED_PEN                                          \
    "This is a pen with a customized name marked on it! The name?\n| " \
    "Well, it depends on who you give it to! " TEXT_MAY_GIFT
#define DESC_HERBAL_SUPPLEMENT \
    "Doubles the stat points earned for your next activity." DESC_BOOST_END1
#define DESC_PORK_TONKOTSU_BOWL \
    "Doubles Guts points earned for your next activity." DESC_BOOST_END1
#define DESC_CHICKEN_KATSU_BOWL \
    "Doubles Knowledge points earned for your next activity." DESC_BOOST_END1
#define DESC_HERBAL_ESSENCE \
    "Doubles the stat points earned when planting in Shujin Academy.\n" DESC_BOOST_END2
#define DESC_GREEN_TEA_SUPPLEMENT \
    "Doubles Confidant points earned hanging out with a confidant." DESC_BOOST_END2
#define DESC_BBB_COMBO                                                  \
    "Adds +1 stat point gained from watching a DVD within the day.\n| " \
    "Effect wears off at the end of a day."

enum eKeyControl
{
    MAP_NORTH,
    MAP_SOUTH,
    MAP_EAST,
    MAP_WEST,
    MENU_UP,
    MENU_DOWN,
    // MENU_LEFT,
    // MENU_RIGHT,
    CONFIRM,
    SCREEN_REFRESH,
    STAT_TOGGLE
};

enum eDayOfWeek
{
    SUNDAY,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY
};

enum ePeriod
{
    AFTERNOON,
    EVENING
};

enum eDisplayMenuMode
{
    ACTIONS,
    ITEMS
};

enum eSelectType
{
    ACT,
    ITEM
};

enum ePlaces
{
    LEBLANC_CAFE,
    BACK_ALLEY,
    CLINIC,
    TRAIN_STATION,
    UNDERGROUND_MALL,
    SHUJIN_ACADEMY,
    SHIBUYA,
    BIG_BANG_BURGER,
    ARCADE,
    AMOUNT_PLACES
};

enum eSocialStats
{
    KINDNESS,
    GUTS,
    KNOWLEDGE,
    AMOUNT_STATS
};

enum eSocialStatPts
{
    SOCIAL_LV1 = 4,
    SOCIAL_LV2 = 12,
    SOCIAL_LV3 = 22
};

enum eConfidants
{
    SOJIRO,
    RYUJI,
    ANN,
    YUSUKE,
    MAKOTO,
    FUTABA,
    HARU,
    TAE,
    SADAYO,
    SUMIRE,
    AMOUNT_CONFIDANTS
};

enum eConfPts
{
    LOCKED = -2,
    UNLOCKABLE = -1,
    CONF_LV1 = 0,
    CONF_LV2 = 7,
    CONF_LV3 = 17,
    CONF_MAX = 18
};

enum eConfEvents
{
    UNLOCK_EVENT = 1,
    MAX_EVENT
};

enum eConfActType
{
    GIVE_GIFT,
    SPEND_TIME,
    CANCEL_CONF
};

enum eItems
{
    /* Both upgrade items and gift items can only be purchased once.
    Upgrade items permanently stay in your inventory once bought,
    while gift items can be gifted to a confidant.
    You cannot purchase another gift if you are already holding one. */

    // UPGRADE_ITEMS

    DVD_PLAYER,
    MUSIC_PLAYER,
    ETIQUETTE_101,
    MYSTERY_CIVILIZATION,
    BRAVERY_DOG,

    // GIFT_ITEMS

    BBB_PLUSH,
    DESK_CLOCK,
    EUCALYPTUS_EXTRACT,
    PERFUME,
    PERSONALIZED_PEN,

    /* Boost items overwrite each other when purchasing more than one at a time.
    Most of them boosts the stat points earned from doing an action
    and are purchasable only once per day. */

    HERBAL_SUPPLEMENT,  // Doubles all stats earned for next stat boost action
    PORK_TONKOTSU_BOWL, // Doubles GUTS      earned ~
    CHICKEN_KATSU_BOWL, // Doubles KNOWLEDGE earned ~
    HERBAL_ESSENCE,     // Doubles KINDNESS  earned from tending to plants
    BBB_COMBO,          // Adds 1 point from watching a DVD
    /* Doubles confidant points earned for hanging out
    (purchasable only when Takemi is unlocked) */
    GREEN_TEA_SUPPLEMENT,
    //
    AMOUNT_ITEMS,
};

/*
Format (aside from General actions)
- DO_<ACTION_NAME> : Actions that boost stats
- HANGOUT_<CONFIDANT>_<LOCATION (IF MULTIPLE): Boost confidant relationship
- SHOP_<SHOP_NAME>: Visit a shop
*/
enum eActions
{
    HANGOUT_SOJIRO,
    HANGOUT_RYUJI_GYM,
    HANGOUT_ANN,
    HANGOUT_YUSUKE,
    HANGOUT_MAKOTO,
    HANGOUT_FUTABA,
    HANGOUT_HARU_GARDEN,
    HANGOUT_TAE,
    HANGOUT_SADAYO,
    HANGOUT_SUMIRE,
    HANGOUT_RYUJI_ARCADE,
    HANGOUT_HARU_BBB,
    JOB_FLOWER,
    JOB_GYUDON,
    JOB_CONVENIENCE,
    SHOP_SECOND_HAND,
    SHOP_VITAMINS,
    SHOP_TONKOTSU,
    SHOP_GIFT,
    SHOP_DVD,
    SHOP_BBB,
    DO_STUDY_LEBLANC,
    DO_WATCH_DVD,
    DO_WARM_BATH,
    DO_TRAIN,
    DO_STUDY_LIBRARY,
    DO_CLEAN,
    DO_PLANTS,
    DO_CAFE,
    DO_FITNESS,
    DO_BBB_CHALLENGE,
    DO_RHYTHM,
    DO_ZOMBIE,
    AMOUNT_ACTIONS
};

/*
    Sets all elements of `aArray` (of size `nSize`) with `nVal`
    @param aArray array of integers
    @param nSize size of `aArray`
    @param nVal value to set all elements of `aArray` with
    @return Every element in `aArray` will be set to `nVal`
*/
void set(int aArray[], int nSize, int nVal)
{
    int i;
    for (i = 0; i < nSize; i++)
        aArray[i] = nVal;
}

/*
    Set `aActionsHere` with all the actions at `nLocation`.
    Note that this only gives all the actions -- whether or not the player
    can actually perform them is dependent on the `getActions()` function in
    `"functions.c"`. Aside from `getActions()`, this function is also used in
    the `getConfsHere()` function to determine the presence of confidants at a
    certain location based on the `HANGOUT_<CONFIDANT>` actions.
    @param nLocation location
    @param aActionsHere array where the actions in the location will be stored
*/
void initActions(int nLocation, int aActionsHere[ACTION_MENU_LIMIT])
{
    int aActionMap[AMOUNT_PLACES][ACTION_MENU_LIMIT];
    for (int i = 0; i < AMOUNT_PLACES; i++)
        set(aActionMap[i], ACTION_MENU_LIMIT, NONE);

    aActionMap[LEBLANC_CAFE][0] = HANGOUT_SOJIRO;
    aActionMap[LEBLANC_CAFE][1] = HANGOUT_FUTABA;
    aActionMap[LEBLANC_CAFE][2] = HANGOUT_SADAYO;
    aActionMap[LEBLANC_CAFE][3] = DO_STUDY_LEBLANC;
    aActionMap[LEBLANC_CAFE][4] = DO_WATCH_DVD;
    aActionMap[BACK_ALLEY][0] = JOB_CONVENIENCE;
    aActionMap[BACK_ALLEY][1] = SHOP_SECOND_HAND;
    aActionMap[BACK_ALLEY][2] = DO_WARM_BATH;
    aActionMap[CLINIC][0] = HANGOUT_TAE;
    aActionMap[CLINIC][1] = SHOP_VITAMINS;
    aActionMap[TRAIN_STATION][0] = HANGOUT_YUSUKE;
    aActionMap[TRAIN_STATION][1] = SHOP_TONKOTSU;
    aActionMap[SHUJIN_ACADEMY][0] = HANGOUT_RYUJI_GYM;
    aActionMap[SHUJIN_ACADEMY][1] = HANGOUT_SUMIRE;
    aActionMap[SHUJIN_ACADEMY][2] = HANGOUT_HARU_GARDEN;
    aActionMap[SHUJIN_ACADEMY][3] = HANGOUT_MAKOTO;
    aActionMap[SHUJIN_ACADEMY][4] = DO_TRAIN;
    aActionMap[SHUJIN_ACADEMY][5] = DO_PLANTS;
    aActionMap[SHUJIN_ACADEMY][6] = DO_STUDY_LIBRARY;
    aActionMap[SHUJIN_ACADEMY][7] = DO_CLEAN;
    aActionMap[SHIBUYA][0] = JOB_GYUDON;
    aActionMap[SHIBUYA][1] = SHOP_DVD;
    aActionMap[SHIBUYA][2] = DO_CAFE;
    aActionMap[SHIBUYA][3] = DO_FITNESS;
    aActionMap[UNDERGROUND_MALL][0] = HANGOUT_ANN;
    aActionMap[UNDERGROUND_MALL][1] = JOB_FLOWER;
    aActionMap[UNDERGROUND_MALL][2] = SHOP_GIFT;
    aActionMap[BIG_BANG_BURGER][0] = HANGOUT_HARU_BBB;
    aActionMap[BIG_BANG_BURGER][1] = SHOP_BBB;
    aActionMap[BIG_BANG_BURGER][2] = DO_BBB_CHALLENGE;
    aActionMap[ARCADE][0] = HANGOUT_RYUJI_ARCADE;
    aActionMap[ARCADE][1] = DO_RHYTHM;
    aActionMap[ARCADE][2] = DO_ZOMBIE;

    for (int i = 0; i < ACTION_MENU_LIMIT; i++)
        aActionsHere[i] = aActionMap[nLocation][i];
}

/*
    Copy the name of the confidant #`nConf` to `sConfName`
    @param sConfName char array to store the result in
    @param nConf confidant number
*/
void copyConfName(char sConfName[CHR_LIMIT], int nConf)
{
    switch (nConf)
    {
        case SOJIRO:
            strcpy(sConfName, "Sojiro");
            break;
        case RYUJI:
            strcpy(sConfName, "Ryuji");
            break;
        case ANN:
            strcpy(sConfName, "Ann");
            break;
        case YUSUKE:
            strcpy(sConfName, "Yusuke");
            break;
        case MAKOTO:
            strcpy(sConfName, "Makoto");
            break;
        case FUTABA:
            strcpy(sConfName, "Futaba");
            break;
        case HARU:
            strcpy(sConfName, "Haru");
            break;
        case TAE:
            strcpy(sConfName, "Takemi");
            break;
        case SADAYO:
            strcpy(sConfName, "Kawakami");
            break;
        case SUMIRE:
            strcpy(sConfName, "Sumire");
            break;
    }
}

/*
    Copy the name of the item #`nItem` to `sItemName`
    @param sItemName char array to store the result in
    @param nConf item number
*/
void copyItemName(char sItemName[CHR_LIMIT], int nItem)
{
    switch (nItem)
    {
        case DVD_PLAYER:
            strcpy(sItemName, "DVD Player");
            break;
        case MUSIC_PLAYER:
            strcpy(sItemName, "Music Player");
            break;
        case ETIQUETTE_101:
            strcpy(sItemName, "Etiquette 101 (DVD)");
            break;
        case MYSTERY_CIVILIZATION:
            strcpy(sItemName, "Mystery of the Ancient Civ. (DVD)");
            break;
        case BRAVERY_DOG:
            strcpy(sItemName, "Bravery the Frightened Dog (DVD)");
            break;
        case BBB_PLUSH:
            strcpy(sItemName, "Big Bang Burger Plushy (GIFT)");
            break;
        case DESK_CLOCK:
            strcpy(sItemName, "Desk Clock (GIFT)");
            break;
        case EUCALYPTUS_EXTRACT:
            strcpy(sItemName, "Eucalyptus Extract (GIFT)");
            break;
        case PERFUME:
            strcpy(sItemName, "Fragrant Perfume (GIFT)");
            break;
        case PERSONALIZED_PEN:
            strcpy(sItemName, "Personalized Pen (GIFT)");
            break;
        case HERBAL_SUPPLEMENT:
            strcpy(sItemName, "Herbal Supplement (BOOST)");
            break;
        case PORK_TONKOTSU_BOWL:
            strcpy(sItemName, "Pork Tonkotsu Bowl (BOOST)");
            break;
        case CHICKEN_KATSU_BOWL:
            strcpy(sItemName, "Chicken Katsu Bowl (BOOST)");
            break;
        case HERBAL_ESSENCE:
            strcpy(sItemName, "Herbal Essence (BOOST)");
            break;
        case BBB_COMBO:
            strcpy(sItemName, "Big Bang Burger Combo (BOOST)");
            break;
        case GREEN_TEA_SUPPLEMENT:
            strcpy(sItemName, "Green Tea Supplement (BOOST)");
            break;
    }
}

/*
    Copy the description of the item #`nItem` to `sItemName`
    @param sItemName char array to store the result in
    @param nConf item number
*/
void copyItemDesc(char sItemName[CHR_LIMIT], int nItem)
{
    switch (nItem)
    {
        case DVD_PLAYER:
            strcpy(sItemName, DESC_DVD_PLAYER);
            break;
        case MUSIC_PLAYER:
            strcpy(sItemName, DESC_MUSIC_PLAYER);
            break;
        case ETIQUETTE_101:
            strcpy(sItemName, DESC_ETIQUETTE_101);
            break;
        case MYSTERY_CIVILIZATION:
            strcpy(sItemName, DESC_MYSTERY_CIVILIZATION);
            break;
        case BRAVERY_DOG:
            strcpy(sItemName, DESC_BRAVERY_DOG);
            break;
        case BBB_PLUSH:
            strcpy(sItemName, DESC_BBB_PLUSH);
            break;
        case DESK_CLOCK:
            strcpy(sItemName, DESC_DESK_CLOCK);
            break;
        case EUCALYPTUS_EXTRACT:
            strcpy(sItemName, DESC_EUCALYPTUS_EXTRACT);
            break;
        case PERFUME:
            strcpy(sItemName, DESC_PERFUME);
            break;
        case PERSONALIZED_PEN:
            strcpy(sItemName, DESC_PERSONALIZED_PEN);
            break;
        case HERBAL_SUPPLEMENT:
            strcpy(sItemName, DESC_HERBAL_SUPPLEMENT);
            break;
        case PORK_TONKOTSU_BOWL:
            strcpy(sItemName, DESC_PORK_TONKOTSU_BOWL);
            break;
        case CHICKEN_KATSU_BOWL:
            strcpy(sItemName, DESC_CHICKEN_KATSU_BOWL);
            break;
        case HERBAL_ESSENCE:
            strcpy(sItemName, DESC_HERBAL_ESSENCE);
            break;
        case BBB_COMBO:
            strcpy(sItemName, DESC_BBB_COMBO);
            break;
        case GREEN_TEA_SUPPLEMENT:
            strcpy(sItemName, DESC_GREEN_TEA_SUPPLEMENT);
            break;
    }
}