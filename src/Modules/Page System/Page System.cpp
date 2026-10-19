#include "Page System.h"
#include "Pages/HomeScreen/HomePage.h"
#include "Pages/Settings/Main/Settings.h"
#include "Pages/Settings/Sim/SimSettings.h"
#include "Pages/Settings/Display/DisplaySettings.h"

// Start on Home page
Page currentPage = PAGE_HOME;
int currentOption = 0;

// Change current page
void SetPage(Page newPage)
{
    currentPage = newPage;
}

// Run the code of the current page
void UpdateCurrentPage()
{
    switch(currentPage)
    {
        case PAGE_HOME:
            HomeScreen();
            break;

        case PAGE_SETTINGS:
            Settings();
            break;

        case PAGE_SIMSETTINGS:
            SimSettingsPage();
            break;

        // case PAGE_ADMINNUMBERSET:
        //     AdminNumberSet();
        //     break;

        case PAGE_DISPLAYSETTINGS:
            displaySettings();
            break;

    }
}