class R3BEventManagerCtrl : public FairEventManager
{
	public:
	R3BEventManagerCtrl(void)
	    : msecs(1000)
	    , evNr(0)
	    , fRootManager(FairRootManager::Instance())
	    , isRunning(kFALSE) {}

	void createControls(void);
	void play(void);
	void pause(void);
	void stop(void);
	void reset(void);
	void nextEvent(void);
	void prevEvent(void);
	void playbackTimerTimeout(void);
	void setEvNr(void);
	void setMsecs(void);

	private:
	TGMainFrame *controls;
	TGNumberEntry *msecsEntry;
	TGNumberEntry *evEntry;
	TTimer *playbackTimer;
	Long_t msecs;
	Long_t evNr;
	Bool_t isRunning;
	FairRootManager *fRootManager;

	ClassDef(R3BEventManagerCtrl, 1)
};

void
R3BEventManagerCtrl::reset()
{
	evEntry->SetIntNumber(0);
	GotoEvent(0);
}

void
R3BEventManagerCtrl::play()
{
	if (isRunning == kFALSE) {
		isRunning = kTRUE;
		printf("Starting timer with '%ld' ms timout.\n", msecs);
		playbackTimer->Start(-1);
	}
}

void
R3BEventManagerCtrl::pause()
{
	if (isRunning == kTRUE) {
		isRunning = kFALSE;
		playbackTimer->TurnOff();
	}
}

void
R3BEventManagerCtrl::stop()
{
	pause();
	reset();
}

void
R3BEventManagerCtrl::playbackTimerTimeout()
{
	nextEvent();
}

void
R3BEventManagerCtrl::setMsecs()
{
	msecs = msecsEntry->GetIntNumber();
	playbackTimer->SetTime(msecs);
	printf("Interval = '%ld' milliseconds.\n", msecs);
	if (isRunning == kTRUE) {
		pause();
		play();
	}
}

void
R3BEventManagerCtrl::prevEvent() {
	if (evNr - 1 < 0) {
		evNr = fRootManager->CheckMaxEventNo() - 1;
	} else {
		evNr--;
	}
	GotoEvent(evNr);
	evEntry->SetIntNumber(evNr);
}

void
R3BEventManagerCtrl::nextEvent()
{
	auto evNrMax = fRootManager->CheckMaxEventNo();
	if (evNr + 1 < evNrMax) {
		evNr++;
	} else {
		evNr = 0;
	}
	GotoEvent(evNr);
	evEntry->SetIntNumber(evNr);
}

void
R3BEventManagerCtrl::setEvNr()
{
	GotoEvent(evEntry->GetIntNumber());
}

void
R3BEventManagerCtrl::createControls()
{
	controls = new TGMainFrame(gClient->GetRoot(),200,40);
	TGHorizontalFrame* hframe = new TGHorizontalFrame(controls,200,40);

	playbackTimer = new TTimer();
	playbackTimer->Connect("Timeout()", "R3BEventManagerCtrl", this,
	    "playbackTimerTimeout()");

	TGTextButton* exit = new TGTextButton(hframe,"&Exit",
	    "gApplication->Terminate(0)");
	TGTextButton* next = new TGTextButton(hframe,"&Next");
	next->Connect("Clicked()","R3BEventManagerCtrl",this,"nextEvent)");
	TGTextButton* prev = new TGTextButton(hframe,"&Prev");
	prev->Connect("Clicked()","R3BEventManagerCtrl",this,"prevEvent()");
	TGTextButton* play = new TGTextButton(hframe,"P&lay");
	play->Connect("Clicked()","R3BEventManagerCtrl",this,"play()");
	TGTextButton* pause = new TGTextButton(hframe,"P&ause");
	pause->Connect("Clicked()","R3BEventManagerCtrl",this,"pause()");
	TGTextButton* stop = new TGTextButton(hframe,"&Stop");
	stop->Connect("Clicked()","R3BEventManagerCtrl",this,"stop()");

	TGLabel *label;
	msecsEntry = new TGNumberEntry(hframe,msecs);
	msecsEntry->Connect("ValueSet(Long_t)", "R3BEventManagerCtrl", this,
	    "setMsecs()");
	(msecsEntry->GetNumberEntry())->Connect("ReturnPressed()",
	    "R3BEventManagerCtrl", this, "setMsecs()");

	evEntry = new TGNumberEntry(hframe,evNr);
	evEntry->Connect("ValueSet(Long_t)", "R3BEventManagerCtrl", this,
	    "setEvNr()");
	(evEntry->GetNumberEntry())->Connect("ReturnPressed()",
	    "R3BEventManagerCtrl", this, "setEvNr()");

	hframe->AddFrame(exit, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
	hframe->AddFrame(prev, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
	hframe->AddFrame(play, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
	hframe->AddFrame(pause, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
	hframe->AddFrame(stop, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
	hframe->AddFrame(next, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
        hframe->AddFrame(new TGLabel(hframe, "mSecs:"),
	    new TGLayoutHints(kLHintsCenterX, 5,5,3,1));
	hframe->AddFrame(msecsEntry, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
        hframe->AddFrame(new TGLabel(hframe, "Event:"),
	    new TGLayoutHints(kLHintsCenterX, 5,5,3,1));
	hframe->AddFrame(evEntry, new TGLayoutHints(kLHintsCenterX,5,5,3,4));

	controls->AddFrame(hframe, new TGLayoutHints(kLHintsCenterX,2,2,2,2));
	controls->SetWindowName("R3B Event Display Controls");
	controls->MapSubwindows();
	controls->Resize(controls->GetDefaultSize());
	controls->MapWindow();

	setMsecs();
}

/* --- MACRO --- */

void
eventDisplay_bl()
{
	FairRunAna *fRun= new FairRunAna();

	FairRuntimeDb* rtdb = fRun->GetRuntimeDb();
	FairParRootFileIo*  parIo1 = new FairParRootFileIo();
	parIo1->open("r3bpar.root");
	rtdb->setFirstInput(parIo1);
	rtdb->print();

	fRun->SetInputFile("r3bsim.root");
	fRun->SetOutputFile("test.root");

	auto *fMan= new R3BEventManagerCtrl();
	FairMCTracks *Track =  new FairMCTracks ("Monte-Carlo Tracks");
	FairMCPointDraw *LandPoints = new FairMCPointDraw ("LandPoint",
	    kOrange,  kFullSquare);

	fMan->AddTask(Track);

	fMan->AddTask(LandPoints);

	fMan->Init();
	fMan->createControls();
}
