#pragma once

// List of all pages in the project
enum Page
{
    PAGE_HOME,
    PAGE_SENSOR,
    PAGE_SETTINGS,
    PAGE_SIMSETTINGS,
    PAGE_ADMINNUMBERSET,
    PAGE_DISPLAYSETTINGS
};

// Stores which page is currently open
extern Page currentPage;

// Change current page
void SetPage(Page newPage);

// Run the current page
void UpdateCurrentPage();

extern int currentOption;