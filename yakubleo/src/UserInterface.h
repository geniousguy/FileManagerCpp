#pragma once
#include <ncurses.h>
#include <filesystem>
#include <memory>
#include <string>
#include "FileSystem.h"
#include <fstream>
#include <regex>

namespace fs = std::filesystem;


/**
 * @class UserInterface
 * @brief Class representing the user interface for file navigation.
 *
 * The UserInterface class provides functionality for navigating and interacting with files in a terminal-based user interface.
 */
class UserInterface
{
public:

    /**
     * @brief Constructor. Initializes the UserInterface variables and a ncruses window.
    */
    UserInterface();

    /**
     * @brief Destructor. Frees ncurses memory.
    */
    ~UserInterface();

    /**
     * @brief Expects user input and calls other functions based on it.
     * @retrun False if q is pressed, true otherwise.
    */
    bool processInput();

    /**
     * @brief Prints the current directory and the whole path to the directory we are currently in.
    */
    void print();

private:
    fs::path m_currentDir; /**< Path to the current directory. */
    FileSystem m_fileSystem; /**< Class that takes care of file operations */
    int m_selectedRow; /**< The index of the selected file. */

    static constexpr int m_normalFileColorPair = 1; /**< The color pair number for normal display. */
    static constexpr int m_selectedFileColorPair = 2; /**< The color pair number for selected display. */

    int m_printFrom; /**< The index of the first file to be printed. */

private:
    /**
     * @brief Enumeration representing the direction of arrow keys.
     */
    enum Direction 
    {
        UP = 1,
        DOWN = 0
    };

private:
    /**
     * @brief Clears the screen and file system representation.
     */
    void removeScreenLeftovers();

    /**
     * @brief Moves the arrow key in the specified direction.
     * @param currentDirection The current direction to move the arrow key.
     */
    void moveArrowKey(Direction currentDirection);

    /**
     * @brief Opens the selected file or directory.
     */
    void open();

    /**
     * @brief Moves to the upper directory.
     */
    void moveToUpperDirectory();

    /**
     * @brief Selects or unselects file at m_selectedRow.
     */
    void selectOrUnselectFile();

     /**
     * @brief Handles the copy command.
     */
    void handleCopy();

    /**
     * @brief Handles the move command.
     */
    void handleMove();

    /**
     * @brief Handles the remove command.
     */
    void handleRemove();

    /**
     * @brief Handles the create command.
     */
    void handleCreate();

    /**
     * @brief Handles the creation of a regular file.
     */
    void handleCreateRegularFile(const std::string& fileName);

    /**
     * @brief Handles the creation of a directory.
     */
    void handleCreateDirectory(const std::string& fileName);

    /**
     * @brief Handles the creation of a symbolic link.
     */
    void handleCreateSymbolicLink(const std::string& fileName);

    /**
     * @brief Prints an error message to the screen at the position specified inside the function.
     * @param message The message to be printed.
    */
    void printErrorMessage(const std::string& message) const;


    /**
     * @brief Reprints the screen with the current directory and the cursour pointing at the selected file.
     */
    void refreshScreenAndClearDirectory();

    /**
     * @brief Selects all the files in m_currentDir that match the regex.
    */
    void handleRegex();

    /**
     * @brief Concatenates selected files into a new file.
     */
    void handleConcatenate();


    /**
     * @brief Selects all the files in m_currentDir that contain the text inputed by user.
     */
    void handleTextSearch();

    /**
     * @brief Finds all the files that are duplicates to the selected file and changes them to symbolic links to the selected file.
     */
    void handleDeduplicate();


 

};