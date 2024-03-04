// events2.c = Events written by me, Justin Rainier Go, in addition to the
// given events.c. Specifically, these are the intro and ending events.

void displayConf(int nConf);
int captureInput();

// Introduction event
void
intro ()
{
	system("cls");
	printf(
	"You are in a cold and dark room, with your hands tied to your back.\n"
	"Detective: You should know your place.\n"
	"Handing you a pen, you weakly write your name...\n\n"
	"\tRen Amamiya\n"
	"\t-----------\n"
	"\t\t\t" FORE_YELLOW "(v)" COLOR_RESET
    " <- When this symbol appears, press any key to continue"
    COLOR_RESET
	);
	captureInput();
	printf("\n"
	"You feel as if this has happened before -- but never mind that.\n"
	"As the dark door opens up, you see a pale face enter the room.\n\n"
	"Attorney: It seems you're coherent. Tell me your account of everything.\n"
	"          Start from the very beginning... (v)"
	);
	captureInput();
	system("cls");
	printf(
	"Tell me your account of everything, once more...\n\n"
	"As you wrap your head around your current situation, you try to remember\n"
	"the days before that incident.\n\n"
	"You tell her everything: how you recently returned to your hometown in\n"
	"Tokyo last September, around two months prior to this current\n"
	"predicament; how you stayed in LeBlanc Cafe, studied in Shujin Academy\n"
	"in the weekdays -- just like you did some time ago. (v)"
	);
	captureInput();
	printf("\n"
	"You told her how you went around, doing activites in the afternoon and evening.\n"
	"You told her how these activies were a learning experience that helped you\n"
	"become kinder, gutsier, and more intelligent. You told her how these traits\n"
	"helped you reconnect with your friends...\n\n"
	"The attorney reflected on this, intent on asking those \"confidants\" of yours\n"
	"for their thoughts...\n\n"
	"This is your recollection of the events prior. (v)"
	);
	captureInput();
	system("cls");
}

/*
    Print Confidant #`nConf`'s testimony of Ren's innocence in the best ending.
    @param nConf
*/
void
printTestimony (int nConf)
{
    switch (nConf)
    {
        case SOJIRO:
            printf(
                "Sojiro: I used to be wary of Ren, but, hoo boy...\n"
                "        He's like a special brew of coffee you can't\n"
                "        really see doing that sort of thing, y'know?"
            );
            break;
        case RYUJI:
            printf(
                "Ryuji: Ren couldn't have done it! As his best friend,\n"
                "       I've seen how he is, and I'd protect him to the end!\n"
                "       ...An accomplice? What's that?"
            );
            break;
        case ANN:
            printf(
                "Ann: Ren is a trustworthy friend that has always been\n"
                "     someone you could count on, despite what you might\n"
                "     think upon first glance."
            );
            break;
        case YUSUKE:
            printf(
                "Yusuke: It is a clear fact of day that Ren did not do the\n"
                "        crime. I won't allow the justice I believe in to be\n"
                "        shaken any further."
            );
            break;
        case MAKOTO:
            printf(
                "Makoto: You of all people should know that Ren is innocent,\n"
                "        and I will continue to say so even if the whole\n"
                "        world believes otherwise, sis!"
            );
            break;
        case FUTABA:
            printf(
                "Futaba: Ren has helped me see the outside world as a\n"
                "        not-so-scary place, so I think him doing this does\n"
                "        not suit him at all, don't you think?"
            );
            break;
        case HARU:
            printf(
                "Haru: Ren-kun is someone that I've honestly depended on a\n"
                "      more times than I can count. There's no way he'd do\n"
                "      something like this."
            );
            break;
        case TAE:
            printf(
                "Takemi: Ren has been a significant person in my medical\n"
                "        contributions. He is not someone that would\n"
                "        easily lie, either."
            );
            break;
        case SADAYO:
            printf(
                "Kawakami: Ren-kun is someone with a strong sense of justice.\n"
                "          As his former teacher, him being accused of a\n"
                "          crime he did not commit is nothing new to me."
            );
            break;
        case SUMIRE:
            printf(
                "Sumire: Senpai? Murder? Never! Senpai has always helped me\n"
                "        ever since we met. He's really, really cool...\n"
                "        ...W-what I'm saying is, senpai would never do it!"
            );
            break;
        default:
            printf("Man: Ren didn't do it!");
    }
}

/*
    Print Confidant #`nConf`'s greetings towards Ren.
    @param nConf
*/
void
printGreetings (int nConf)
{
    switch (nConf)
    {
        case SOJIRO:
            printf(
                "Sojiro: Hoo boy, now that was something. To celebrate your\n"
                "        release, I've made some special curry for everyone.\n"
                "        Want some coffee as well, Ren? Or do you want to\n"
                "        make it yourself?"
            );
            break;
        case RYUJI:
            printf(
                "Ryuji: Ren, this Halloween Party is great for real! Wonder\n"
                "       why I felt deja vu about this whole situation,\n"
                "       though. Are there any Personas that rewrite- no,\n"
                "       repeat history?"
            );
            break;
        case ANN:
            printf(
                "Ann: It's a good thing you're safe and sound, Ren. \n"
                "     Oh! Is that a shooting star? Did anyone see that?"
            );
            break;
        case YUSUKE:
            printf(
                "Yusuke: This party is so picturesque, I wonder how I might\n"
                "        be able to replicate this on a painting!"
            );
            break;
        case MAKOTO:
            printf(
                "Makoto: Oh, Ren, I knew you were innocent from the very\n"
                "        start. I guess I should stop worrying about that now\n"
                "        that we're here, though..."
            );
            break;
        case FUTABA:
            printf(
                "Futaba: There's a lot of people here. Ooh, is that Turkey?\n"
                "        I knew Dad would cook some for me- I mean us!\n"
                "        That's my favorite!"
            );
            break;
        case HARU:
            printf(
                "Haru: Hi Ren! I brought some extra food from Big Bang Burger\n"
                "      that we may all share together! Consider it\n"
                "      \"on the house\"!"
            );
            break;
        case TAE:
            printf(
                "Takemi: Once you're done eating dinner, why not try these\n"
                "        vitamins, Ren? Haha, I guess not. Maybe some other\n"
                "        time; you DID just come out of prison, after all...\n"
                "        Oh? Jail? What's the difference?"
            );
            break;
        case SADAYO:
            printf(
                "Kawakami: Ren-kun! It's a good thing nothing bad happened\n"
                "          after all. Your future looks bright, heading to\n"
                "          university... Oh, but I'm getting ahead of myself!\n"
                "          Let's enjoy tonight!"
            );
            break;
        case SUMIRE:
            printf(
                "Sumire: I'm kind of sleepy, Senpai... But it's alright!\n"
                "        We're here to celebrate your release!\n"
                "        But maybe some coffee would be nice..."
            );
            break;
        default:
            printf("Man: Greetings, Ren! Nice party we're having, eh?\n");
    }
}

/*
    Print Confidant #`nConf`'s check up towards Ren in the bad ending.
    @param nConf
*/
void
printCheckup (int nConf)
{
    switch (nConf)
    {
        case SOJIRO:
            printf(
                "Sojiro: I hope you're OK, Ren. The court believes in your\n"
                "innocence, so I wonder why they placed you under probation\n"
                "anyway."
            );
            break;
        case RYUJI:
            printf(
                "Ryuji: Ren! Are you OK in there? Wait, you're not in prison?\n"
                "       For real!? That's good! But you're under probation?\n"
                "       Aww... I'm here for you if you need me. See ya!"
            );
            break;
        case ANN:
            printf(
                "Ann: Ren, you OK? It's a shame you're under probation for\n"
                "     this, even though you're innocent. If you need any help\n"
                "     then feel free to talk with me anytime."
            );
            break;
        case YUSUKE:
            printf(
                "Yusuke: Ren, it pains me to see you under probation. What\n"
                "        cruel artist of fate wishes to see you in this\n"
                "        predicament? Let me assure you that you are free,\n"
                "        that is, free to approach me about your worries."
            );
            break;
        case MAKOTO:
            printf(
                "Makoto: Ren, let me get straight to the point. Logically,\n"
                "        the real culprit is the reason why you're under\n"
                "        probation right now. Sis and I are still working\n"
                "        on figuring the case out, but I'm afraid you'll have\n"
                "        to make do for now. I'm here for you, be seeing you."
            );
            break;
        case FUTABA:
            printf(
                "Futaba: Ren, I know I'm really nearby, but I thought I\n"
                "        should call to be safe. Man, they really screwed up,\n"
                "        didn't they? Why be under probation when you're so\n"
                "        obviously innocent?"
            );
            break;
        case HARU:
            printf(
                "Haru: Ren? Many people have probably been calling you now,\n"
                "      so I hope you don't mind me doing the same. Just know\n"
                "      that everyone's here to support you when you need to."
            );
            break;
        case TAE:
            printf(
                "Takemi: Man, now that you're under probation, we probably\n"
                "        can't meet each other at the usual spot, huh?\n"
                "        Don't worry about me, Ren. I should be the one to\n"
                "        worry about you."
            );
            break;
        case SADAYO:
            printf(
                "Kawakami: Ren-kun, I believe in your innocence. While I used\n"
                "          to treat you coldly because of your record,\n"
                "          know that you can still ask me for help even while\n"
                "          under probation."
            );
            break;
        case SUMIRE:
            printf(
                "Sumire: Senpai! I hope we'll still be able to do things\n"
                "        together even though you're under probation."
            );
            break;
        default:
            printf("Man: I hope you're doing well, Ren.\n");
    }
}

/*
    Try to print all the testimonies of the maxed out confidants.
    @param aConfPts confidant points for all confidants
*/
void tryPrintAllTestimonies(int aConfPts[AMOUNT_CONFIDANTS])
{
    int nConf;
    for (nConf = SOJIRO; nConf < AMOUNT_CONFIDANTS; nConf++)
    {
        if (aConfPts[nConf] == CONF_MAX)
        {
            printTestimony(nConf);
            printf("\n");
        }
    }
    printf(FORE_YELLOW " (v)\n" COLOR_RESET);
    captureInput();
}

/*
    Try to print all the greetings of the maxed out confidants.
    @param aConfPts confidant points for all confidants
*/
void tryPrintAllGreetings(int aConfPts[AMOUNT_CONFIDANTS])
{
    int nConf;
    for (nConf = SOJIRO; nConf < AMOUNT_CONFIDANTS; nConf++)
    {
        if (aConfPts[nConf] == CONF_MAX)
        {
            printGreetings(nConf);
            printf("\n");
        }
    }
    printf(FORE_YELLOW " (v)\n" COLOR_RESET);
    captureInput();
}

/*
    Try to print all the check ups of the maxed out confidants.
    @param aConfPts confidant points for all confidants
*/
void tryPrintAllCheckups(int aConfPts[AMOUNT_CONFIDANTS])
{
    int nConf;
    for (nConf = SOJIRO; nConf < AMOUNT_CONFIDANTS; nConf++)
    {
        if (aConfPts[nConf] == CONF_MAX)
        {
            printCheckup(nConf);
            printf("\n");
        }
    }
    printf(FORE_YELLOW " (v)\n" COLOR_RESET);
    captureInput();
}

/*
    The ending event. There are four possible endings that may be achieved
    based on how many confidants you reached MAX level with.
*/
void
ending (int aConfPts[])
{
    int nConf;
    int nNumMaxedOutConfs = 0;
	system("cls");
    printf(
        "...And that's what happened.\n"
        "\t\t\t" FORE_YELLOW "(v)" COLOR_RESET
        "<- When this symbol appears, press any key to continue\n"
        COLOR_RESET
        );
    captureInput();

    printf(
        "One by one, the defense attorney, Sae Niijima, contacted the people\n"
        "you said you grew close with...\n\n"
    );

    // Count maxed out confidants
    for (nConf = SOJIRO; nConf < AMOUNT_CONFIDANTS; nConf++)
    {
        if (aConfPts[nConf] == CONF_MAX)
        {
            nNumMaxedOutConfs++;
        }
    }

    if (nNumMaxedOutConfs == 0)
    {
        printf("But nobody came.\n\n");
        printf("(v)");
        captureInput();
    }

    if (nNumMaxedOutConfs == AMOUNT_CONFIDANTS) // PERFECT ENDING
    {
        tryPrintAllTestimonies(aConfPts);
        printf(
            "Later, in the interrogation room, Sae Niijima appears with some\n"
            "paperwork. She looks happy.\n"
            "Niijima: You are hereby absolved of the crime and anything\n"
            "         to it. Enjoy your freedom, Ren! (v)\n"
            "---------------------------------------------------------------\n"
            "At LeBlanc Cafe, Ren enjoys a belated Halloween party with\n"
            "everyone...\n\n"
        );
        tryPrintAllGreetings(aConfPts);
        printf("PERFECT ENDING achieved! Congratulations!\n");
    }
    else if (nNumMaxedOutConfs >= 7) // GOOD ENDING
    {
        printf(
            "Later, in the interrogation room, Sae Niijima appears with some\n"
            "paperwork...\n"
            "Niijima: Due to lack of evidence, it has been seen fit that\n"
            "         you are declared innocent. You are set free, Ren!\n"
            "---------------------------------------------------------------\n"
            "At LeBlanc Cafe, Ren enjoys a small and simple dinner with\n"
            "his friends...\n\n"
        );
        tryPrintAllGreetings(aConfPts);
        if (aConfPts[FUTABA] == CONF_MAX)
        {
            printf("Of course, Sojiro didn't forget Futaba's favorite:\n"
                   "Turkey!\n\n");
        }
        printf("GOOD ENDING achieved!\n");
        printf("Can you reach the PERFECT ENDING?\n");
    }
    else if (nNumMaxedOutConfs >= 4) // NEUTRAL ENDING
    {
        printf(
            "Later, in the interrogation room, Sae Niijima appears with some\n"
            "paperwork.\n"
            "Niijima: Due to lack of evidence, it has been seen fit that\n"
            "         you are declared innocent."
            "Suddenly, Niijima's phone rang. Picking it up, her expression\n"
            "saddened a little bit.\n"
            "Niijima: Unfortunately, you will be placed under probation.\n"
            "         that means you'll have an officer watching over you.\n"
            "         better than being arrested outright, I suppose...\n"
            "---------------------------------------------------------------\n"
            "At LeBlanc Cafe, Ren receives a few phone calls from\n"
            "his friends...\n\n"
        );
        tryPrintAllCheckups(aConfPts);
        printf("NEUTRAL ENDING achieved!\n");
        printf("Try for a better ending next time!\n");
    }
    else // BAD ENDING
    {
        printf(
            "Later, the detective returned.\n"
            "Detective: That paper you signed? That was a confession.\n"
            "           No one's around to accuse us of anything funny, so\n"
            "           you're all alone, kiddo!\n"
            "---------------------------------------------------------------\n"
            "Prison life... You were not able to change the hearts of the\n"
            "Japanese court system. Unfortunately, despite your innocence,\n"
            "you ended up being sent to prison. You await your hearing...\n\n"
        );
        if (aConfPts[MAKOTO] == CONF_MAX)
        {
            printf(
                "Suddenly, the guards tell you that someone has been calling\n"
                "for you on the prison phone. You pick it up, and hear a\n"
                "familiar voice...\n\n"
                "Niijima: Ren, I know your situation looks bleak right now,\n"
                "         but rest assured, I will have you released!\n"
                "Hearing this, you feel a small glimmer of hope.\n\n"
            );
        }
        printf("BAD ENDING achieved...\n");
        printf("To get a better ending, try to be a friendlier person!\n");
    }
    printf("Press any key to end the game.\n");
    captureInput();
}