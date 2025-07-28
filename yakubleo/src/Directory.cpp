#include "Directory.h"

Directory::Directory(const fs::path &pathToFile) : File(pathToFile)
{

}


void Directory::copy(const fs::path &destination)
{
    fs::path destinationFilename = destination / m_pathToFile.filename();
    fs::copy(m_pathToFile, destinationFilename ,fs::copy_options::recursive | fs::copy_options::overwrite_existing);

}

void Directory::move(const fs::path &destination)
{
    fs::rename(m_pathToFile, destination / m_pathToFile.filename());
}

void Directory::remove()
{
    fs::remove_all(m_pathToFile);
}


void Directory::print(int row, int column, int normalColour, int selectedColour ) const
{

    attron(A_NORMAL);
    mvprintw(row, column, "[D] ");
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

void Directory::appendContentsTo(std::ofstream &outputStream) const
{
    // Do nothing
}

void Directory::selectOnText(const std::string &text)
{
    // Do nothing
}

File *Directory::clone() const
{
    return new Directory(*this);
}

bool Directory::isEqualTo(const File &otherFile) const
{
    return false;
}

std::string Directory::getContents() const
{
    return "";
}

void Directory::changeToSymbolicLink(const File &fileToPointAt)
{
    // Do nothing
}
