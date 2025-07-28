#include "RegularFile.h"

RegularFile::RegularFile(const fs::path &pathToFile) : File(pathToFile)
{

}



void RegularFile::copy(const fs::path &destination)
{
    fs::path destinationFilename = destination / m_pathToFile.filename();
    fs::copy_file(m_pathToFile, destinationFilename, fs::copy_options::overwrite_existing);
}

void RegularFile::move(const fs::path &destination)
{
    fs::rename(m_pathToFile, destination / m_pathToFile.filename());
}

void RegularFile::remove()
{
    fs::remove(m_pathToFile);
}

void RegularFile::print(int row, int column, int normalColour, int selectedColour) const
{
    attron(A_DIM);
    mvprintw(row, column, "[F] ");
    attroff(A_DIM);

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

void RegularFile::appendContentsTo(std::ofstream &outputStream) const
{
    std::ifstream inputFile(m_pathToFile);
    if (inputFile.is_open()) 
    {
        outputStream << inputFile.rdbuf();
        inputFile.close();
    } 
    else 
    {
        throw std::runtime_error("Could not open file " + m_pathToFile.string());
    }
}

void RegularFile::selectOnText(const std::string &text)
{
    std::ifstream inputFile(m_pathToFile);
    if (inputFile.is_open()) 
    {
        std::string fileContents;
        while (std::getline(inputFile, fileContents)) 
        {
            if(fileContents.find(text) != std::string::npos)
            {
                m_isSelected = true;
                break;
            }
        }
        inputFile.close();
    } 
    else 
    {
        throw std::runtime_error("Could not open file " + m_pathToFile.string());
    }
}

File *RegularFile::clone() const
{
    return new RegularFile(*this);
}

bool RegularFile::isEqualTo(const File &otherFile) const
{
    return getContents() == otherFile.getContents();
}

std::string RegularFile::getContents() const
{
    std::ifstream file(m_pathToFile);

    if(!file.is_open())
    {
        throw std::runtime_error("Could not open file " + m_pathToFile.string());
    }

    return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

void RegularFile::changeToSymbolicLink(const File &fileToPointAt)
{
    fs::path pathToPointAt = fileToPointAt.getPath();
    fs::path currentPath = m_pathToFile;

    fs::remove(currentPath);
    fs::create_symlink(pathToPointAt, currentPath);
}
