#include "SmallWindow.h"

SmallWindow::SmallWindow(const char * windowTitle)
{
    m_windowTitle = strdup(windowTitle);
    
    m_window = derwin(stdscr, m_windowRows, m_windowColumns, m_windowStartY, m_windowStartX);
    box(m_window, 0, 0);
    mvwprintw(m_window, m_titleStartY, m_titleStartX,"%s", windowTitle); 
    wrefresh(m_window);

    // Create fields nessesary for the form
    // int formRows = m_windowRows - 2;
    // int formColumns = m_windowColumns - 2;
    m_fields[0] = new_field(m_formRows, m_formColumns, 0, 0, 0, 0); // rows = 1, cols = 10
    m_fields[1] = NULL;

    // Set field options so that it is scrollable and editable
    set_field_opts(m_fields[0], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE );

    // set_field_back(m_fields[0], A_UNDERLINE); // print a line under the field, good for debugging

    // Create the form and post it
    m_form = new_form(m_fields);

    // bind form to our window 
    set_form_win(m_form, m_window);
    set_form_sub(m_form, derwin(m_window, m_formRows, m_formColumns, m_formStartY, m_formStartX));

    post_form(m_form);
    refresh();
    wrefresh(m_window);

}

SmallWindow::~SmallWindow()
{

    unpost_form(m_form);
    free_form(m_form);
    free_field(m_fields[0]);

    delwin(m_window);
    free((void*)m_windowTitle);

}

std::string SmallWindow::input() const
{
    
    processInput();
    form_driver(m_form, REQ_VALIDATION);
    char *input = field_buffer(m_fields[0], 0);

    std::string inputInString(input);

    stripTrailingSpaces(inputInString);

    return inputInString;
}

std::string SmallWindow::getDestinationDirectory() const
{
    std::string input = this->input();

    fs::path destination = input;
    
    if (fs::exists(destination))
    {
        if (fs::is_directory(destination))
        {
            printMessage("The directory exists.");
            input = destination.c_str();
            getch();
            refresh();
        }
        else
        {
            printMessage("The entry is not a directory.");
            input = "";
            getch();
            refresh();
        }
    }
    else
    {
        printMessage("The entry does not exist.");
        input = "";
        getch();
        refresh();
    }

    erase();
    refresh();
    return input;
}

void SmallWindow::processInput() const
{
    int ch;
    while ((ch = getch()) != '\n')
    {
        switch (ch)
        {
        case KEY_LEFT:
            form_driver(m_form, REQ_PREV_CHAR);
            break;
        case KEY_RIGHT:
            form_driver(m_form, REQ_NEXT_CHAR);
            break;
        case KEY_BACKSPACE:
            form_driver(m_form, REQ_DEL_PREV);
            break;
        // Delete key
        case KEY_DC:
            form_driver(m_form, REQ_DEL_CHAR);
            break;
        default:
            // If this is a printable character, it gets printed
            if (isprint(ch))
                form_driver(m_form, ch);
            break;
        }
    }
}

void SmallWindow::stripTrailingSpaces(std::string &inputString) const
{
    while(!inputString.empty() && inputString.back() == ' ')
    {
        inputString.pop_back();
    }
}

void SmallWindow::printMessage(const std::string &message) const
{
    form_driver(m_form, REQ_CLR_FIELD);
    wprintw(m_window, "%s", message.c_str());
}
