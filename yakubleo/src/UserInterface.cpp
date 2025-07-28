#include "UserInterface.h"
#include "SmallWindow.h"


UserInterface::UserInterface() : m_currentDir(fs::current_path()), m_fileSystem(m_currentDir), m_selectedRow(0), m_printFrom(0)
{
    // Initialize screen
    // Setup memory
    // Clear screen
    initscr();

    // Initialises colors
    start_color();
    init_pair(m_normalFileColorPair, COLOR_RED, COLOR_BLACK);
    init_pair(m_selectedFileColorPair, COLOR_BLUE, COLOR_BLACK);

    // Disables line buffering and allows characters to be read immediately without waiting for a newline. This is useful for receiving user input without requiring the Enter key to be pressed
    cbreak();

    // Disable reading characters showing up on the screen
    noecho();

    // This function enables the keypad of the terminal, allowing it to generate special function key codes (such as arrow keys) instead of treating them as regular characters
    keypad(stdscr, true);

    m_fileSystem.setPointedAt(m_selectedRow); // Set the first file to be pointed at to highlight it

    // scrollok(stdscr, TRUE); // Allow scrolling
}

UserInterface::~UserInterface()
{
    // Deallocate memory
    // End encurses
    endwin();
}

void UserInterface::removeScreenLeftovers()
{
    clear();
    m_fileSystem.clearFileSystem();
    m_selectedRow = 0;
    m_printFrom = 0;
}

void UserInterface::moveArrowKey(Direction currentDirection)
{
    switch (currentDirection)
    {
    case UP:
        if (m_selectedRow > 0)
        {
            m_fileSystem.dePointAt(m_selectedRow);
            m_selectedRow--;
            m_fileSystem.setPointedAt(m_selectedRow);

            if(m_selectedRow < m_printFrom)
            {
                m_printFrom--;
                clear();
            }
        }
        break;
    case DOWN:
    {
        int totalRows = m_fileSystem.filesInCurrentDirectory();
        if (m_selectedRow < totalRows - 1)
        {
            m_fileSystem.dePointAt(m_selectedRow);
            m_selectedRow++;
            m_fileSystem.setPointedAt(m_selectedRow);

            if(m_selectedRow >= m_printFrom + LINES - 2)
            {
                m_printFrom++;
                clear();
            }
        }
    }
    break;
    default:
        break;
    }
}

void UserInterface::open()
{
    int row = 0;
    for (const auto &entry : fs::directory_iterator(m_currentDir))
    {
        if (row == m_selectedRow)
        {
            if (entry.is_directory())
            {
                m_currentDir = entry.path();
                refreshScreenAndClearDirectory();
                return;
            }
        }
        row++;
    }
}

void UserInterface::moveToUpperDirectory()
{
    m_currentDir = m_currentDir.parent_path();
    refreshScreenAndClearDirectory();   
}

void UserInterface::selectOrUnselectFile()
{
    m_fileSystem.setSelectedAt(m_selectedRow);
}
bool UserInterface::processInput()
{
    int ch = getch();
    switch (ch)
    {
    case KEY_UP:
        moveArrowKey(UP);
        break;
    case KEY_DOWN:
        moveArrowKey(DOWN);
        break;
    case '\n':
        try
        {
            open();
        }
        catch (const std::exception &e)
        {
            printErrorMessage("Cannot open directory");
            m_currentDir = fs::current_path();
            refreshScreenAndClearDirectory();
        }
        break;
    case 'u':
        moveToUpperDirectory();
        break;
    case 's':
        selectOrUnselectFile();
        break;
    case 'c':
        try
        {
            handleCopy();
        }
        catch(const std::exception& e)
        {
            printErrorMessage("Cannot copy one of the files.");
        }
        break;
    case 'm':
        try
        {
            handleMove();
        }
        catch(const std::exception& e)
        {
            printErrorMessage("Cannot move one of the files.");
        }
        break;
    case 'd':
        try
        {
            handleRemove();
        }
        catch(const std::exception& e)
        {
            printErrorMessage("Cannot remove one of the files.");
        }
        break;
    case 'a':
        try
        {
            handleCreate();
        }
        catch(const std::exception& e)
        {
            printErrorMessage("Cannot create a file.");
        }
        break;
    case 'r':
        try
        {
            handleRegex();
        }
        catch(const std::exception& e)
        {
            printErrorMessage("Something went wrong...");
        }
        break;
    case 'o':
        try
        {
            handleConcatenate();
        }
        catch(const std::exception& e)
        {
            printErrorMessage("Cannot concatenate files.");
        }
        break;
    case 't':
        try
        {
            handleTextSearch();
        }
        catch(const std::exception& e)
        {
            printErrorMessage("Cannot search for text in one of the files.");
        }
        break;
    case 'p':
        try
        {
            handleDeduplicate();
        }
        catch(const std::exception& e)
        {
            printErrorMessage(e.what());
        }
        break;
    case 'q':
        return false;
    default:
        break;
    }
    return true;
}

void UserInterface::print()
{
    mvprintw(0, 0, "%s", m_currentDir.c_str());
    m_fileSystem.print(1, 0, m_normalFileColorPair, m_selectedFileColorPair, m_printFrom, size_t(m_printFrom + LINES - 2) );
    refresh();
}

void UserInterface::handleCopy()
{
    SmallWindow inputWindow("Enter copy destination directory");
    std::string destination = inputWindow.getDestinationDirectory();

    if(destination.empty())
    {
        return;
    }

    m_fileSystem.copySelectedFiles(destination);

}

void UserInterface::handleMove()
{
    SmallWindow inputWindow("Enter move destination directory");
    std::string destination = inputWindow.getDestinationDirectory();

    if(destination.empty())
    {
        return;
    }

    m_fileSystem.moveSelectedFiles(destination);

    
    refreshScreenAndClearDirectory();
}

void UserInterface::handleRemove()
{
    m_fileSystem.removeSelectedFiles();
    refreshScreenAndClearDirectory();
}

void UserInterface::handleCreate()
{
    SmallWindow inputWindow("Enter file type: RF (1), D (2), SL (3)");
    std::string selectedOption = inputWindow.input();
    
    if(selectedOption != "1" && selectedOption != "2" && selectedOption != "3")
    {
        printErrorMessage("Invalid option");
        refreshScreenAndClearDirectory();
        return;
    }
        
    SmallWindow inputWindow2("Enter file name");
    std::string fileName = inputWindow2.input();

    switch (std::stoi(selectedOption))
    {
    case 1:
        {
            handleCreateRegularFile(fileName);
        }
        break;
    case 2:
        {
            handleCreateDirectory(fileName);
        }
        break;
    case 3:
        {
            try
            {
                handleCreateSymbolicLink(fileName);    
            }
            catch(const std::exception& e)
            {
                printErrorMessage("Cannot create symbolic link, file with that name already exists");
            }
        }
        break;
    default:    
        break;
    }

    refreshScreenAndClearDirectory();
}

void UserInterface::handleCreateRegularFile(const std::string &fileName)
{
    std::ofstream file(m_currentDir / fileName);
}

void UserInterface::handleCreateDirectory(const std::string &fileName)
{
    fs::create_directory(m_currentDir / fileName);
}

void UserInterface::handleCreateSymbolicLink(const std::string &fileName)
{
    SmallWindow inputWindow("Enter path of file to point to");
    std::string pathToPointTo = inputWindow.input();

    if(pathToPointTo.empty())
    {
        return;
    }

    fs::create_symlink(pathToPointTo, m_currentDir / fileName);
    
}

void UserInterface::printErrorMessage(const std::string &message) const
{
    clear();
    mvprintw(0, 0, "Error: %s", message.c_str());
    getch();
    clear();
}

void UserInterface::refreshScreenAndClearDirectory()
{
    removeScreenLeftovers();
    m_fileSystem.loadFiles(m_currentDir);
    m_fileSystem.setPointedAt(m_selectedRow);
}

void UserInterface::handleRegex()
{
    SmallWindow inputWindow("Enter regex pattern");
    std::string inputString = inputWindow.input();
    
    std::regex regexPattern;
    try
    {
        regexPattern = inputString;
    }
    catch(const std::exception& e)
    {
        printErrorMessage("Invalid regex pattern");
        refreshScreenAndClearDirectory();
        return;
    }

    m_fileSystem.selectOnRegex(regexPattern);

    clear();

}

void UserInterface::handleConcatenate()
{
    SmallWindow inputWindow("Concatenate selected files into:");
    std::string fileName = inputWindow.input();

    std::ofstream outputFile;

    try
    {
        outputFile = m_currentDir / fileName;
    }
    catch(const std::exception& e)
    {
        printErrorMessage("Cannot create file with that name");
        refreshScreenAndClearDirectory();
        return;
    }

    m_fileSystem.appendSelectedFilesTo(outputFile);

    outputFile.close();

    refreshScreenAndClearDirectory();
}

void UserInterface::handleTextSearch()
{
    SmallWindow inputWindow("Enter text to search for");
    std::string textToSearchFor = inputWindow.input();

    m_fileSystem.selectOnText(textToSearchFor);

    clear();
}

void UserInterface::handleDeduplicate()
{
    if(m_fileSystem.selectedFilesCount() != 1)
    {
        printErrorMessage("Please select exactly one file");
        refreshScreenAndClearDirectory();
        return;
    }

    SmallWindow inputWindow("Enter directory you suspect has duplicates");
    fs::path directoryToSearchIn = inputWindow.getDestinationDirectory();

    if(directoryToSearchIn == m_currentDir)
    {
        m_fileSystem.deduplicateSelectedFileInCurrentDirectory();
    }
    else
    {
        m_fileSystem.deduplicateSelectedFileIn(directoryToSearchIn);
    }

    refreshScreenAndClearDirectory();
}
