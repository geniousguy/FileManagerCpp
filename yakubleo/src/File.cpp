#include "File.h"

File::File(const fs::path &pathToFile) : m_pathToFile(pathToFile), m_isSelected(false), m_isPointedAt(false)
{
}

void File::select()
{
    if(m_isSelected)
    {
        m_isSelected = false;
    }
    else
    {
        m_isSelected = true;
    }
}

void File::deSelect()
{
    m_isSelected = false;
}

void File::setPointed()
{
    m_isPointedAt = true;
}

void File::dePoint()
{
    m_isPointedAt = false;
}

void File::selectOnRegex(const std::regex &regularExpression)
{
    if(std::regex_match(m_pathToFile.filename().string(), regularExpression))
    {
        m_isSelected = true;
    }
}

std::string File::getName() const
{
    return m_pathToFile.filename().string();
}

fs::path File::getPath() const
{
    return m_pathToFile;
}

bool File::isSelected() const
{
    return m_isSelected;
}
