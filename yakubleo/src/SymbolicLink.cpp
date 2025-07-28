#include "SymbolicLink.h"

SymbolicLink::SymbolicLink(const fs::path &pathToFile) : File(pathToFile)
{
}


void SymbolicLink::copy(const fs::path &destination)
{
    fs::path destinationFilename = destination / m_pathToFile.filename();

    fs::copy_symlink(m_pathToFile, destinationFilename);

}

void SymbolicLink::move(const fs::path &destination)
{
    fs::rename(m_pathToFile, destination / m_pathToFile.filename());
}

void SymbolicLink::remove()
{
    fs::remove(m_pathToFile);
}

void SymbolicLink::print(int row, int column, int normalColour, int selectedColour )const
{
    attron(A_NORMAL);
    mvprintw(row, column, "[S] ");
    attroff(A_NORMAL);


    int indent = 4;
    if(m_isPointedAt)
    {
        
        attron(COLOR_PAIR(normalColour));
        attron(A_REVERSE);
        mvprintw(row, column + indent, " %s", m_pathToFile.filename().c_str());
        attroff(A_REVERSE);
        attroff(COLOR_PAIR(normalColour));
    }
    else if(m_isSelected)
    {
        attron(COLOR_PAIR(selectedColour));
        mvprintw(row, column + indent, " %s", m_pathToFile.filename().c_str());
        attroff(COLOR_PAIR(selectedColour));
    }
    else
    {
        attron(COLOR_PAIR(normalColour));
        mvprintw(row, column + indent, " %s", m_pathToFile.filename().c_str());
        attroff(COLOR_PAIR(normalColour));
    }

    if(m_isPointedAt && m_isSelected)
    {
        attron(COLOR_PAIR(selectedColour));
        attron(A_REVERSE);
        mvprintw(row, column + indent, " %s", m_pathToFile.filename().c_str());
        attroff(A_REVERSE);
        attroff(COLOR_PAIR(selectedColour));
    }
}

void SymbolicLink::appendContentsTo(std::ofstream &outputStream) const
{
    // Do nothing
}

void SymbolicLink::selectOnText(const std::string &text)
{
    // Do nothing
}

File *SymbolicLink::clone() const
{
    return new SymbolicLink(*this);
}

bool SymbolicLink::isEqualTo(const File &otherFile) const
{
    return false;
}

std::string SymbolicLink::getContents() const
{
    return "";
}

void SymbolicLink::changeToSymbolicLink(const File &fileToPointAt)
{
    // Do nothing
}
