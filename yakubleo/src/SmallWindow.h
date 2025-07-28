#pragma once
#include <ncurses.h>
#include <cstring>
#include <cstdlib>
#include <string>
#include <filesystem>
#include <form.h>

namespace fs = std::filesystem;


/**
 * @class SmallWindow
 * @brief Class representing a small ncurses window.
 *
 * The SmallWindow class provides functionality for creating a small ncurses window and reading input from it.
 */
class SmallWindow
{
public:
    /**
     * @brief Constructor. Creates a small ncurses window. And enables echo.
     * @param windowTitle The title of the window.
     * 
     * Creates a small window and prints it on the screen.
     */
    SmallWindow(const char * windowTitle);

    /**
     * @brief Destructor. Frees ncurses memory. And disables echo.
     */
    ~SmallWindow();
    /**
     * @brief Reads input from the window of max 1000 characters.
     * @return The input from the user.
     */
    std::string input() const;

    /**
     * @brief Gets the destination directory from the user.
     * @return The destination directory, or an empty string if the directory inputed by user does not exist.
     */
    std::string getDestinationDirectory() const;

    /**
     * @brief Prints a message on the window.
     * @param message The message to print.
     */
    void printMessage(const std::string &message) const;


private:
    const char *m_windowTitle; /**< The title of the window. */
    WINDOW* m_window; /**< The ncurses window. */
    FIELD *m_fields[2]; /**< The ncurses field. */
    FORM *m_form; /**< The ncurses form. */


    int m_windowColumns = 50; /**< The number of columns of the window. */
    int m_windowRows = 3; /**< The number of rows of the window. */

    int m_formRows = m_windowRows - 2; /**< The number of rows of the form. */
    int m_formColumns = m_windowColumns - 2; /**< The number of columns of the form. */

    int m_windowStartX = (COLS - 50) / 2; /**< The x coordinate of the window. */
    int m_windowStartY = (LINES - 5) / 2; /**< The y coordinate of the window. */

    int m_titleStartX = 1; /**< The x coordinate of the title relative to the window. */
    int m_titleStartY = 0; /**< The y coordinate of the title relative to the window. */

    int m_formStartX = 1; /**< The x coordinate of the form relative to the window. 1 pos is recommended */  
    int m_formStartY = 1; /**< The y coordinate of the form relative to the window. 1 pos is recommended */ 


private:
    /**
     * @brief Processes the input from the user.
     */
    void processInput()const;

    /**
     * @brief Strips the trailing spaces from the input string.
     * @param string The string to strip the trailing spaces from.
     * @return The input string without trailing spaces.
     *
     * Needed, because ncurses fills the form with spaces.
     */
    void stripTrailingSpaces(std::string &inputString) const;

};