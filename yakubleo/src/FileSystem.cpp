#include "FileSystem.h"

FileSystem::FileSystem(const fs::path &directory)
{
    loadFiles(directory);
}

void FileSystem::print(int initialRow, int initialColumn, int normalFileColourPair, int selectedFileColourPair, int printFrom, size_t totalLinesInTerminal) const
{

    int row = initialRow ;
    int column = initialColumn;

    for(size_t i = printFrom; i < m_filesInDirectory.size() && i < totalLinesInTerminal; i++)
    {
        m_filesInDirectory[i]->print(row, column, normalFileColourPair, selectedFileColourPair);
        row++;
    }
}

void FileSystem::loadFiles(const fs::path &directory)
{
    for (const auto& entry : fs::directory_iterator(directory))
    {
        if (entry.is_symlink())
        {
            m_filesInDirectory.emplace_back(std::make_unique<SymbolicLink>(entry.path()));
        }
        else if (entry.is_directory())
        {
            m_filesInDirectory.emplace_back(std::make_unique<Directory>(entry.path()));
        }
        else if (entry.is_regular_file())
        {
            m_filesInDirectory.emplace_back(std::make_unique<RegularFile>(entry.path()));
        }
    }
}

void FileSystem::clearFileSystem()
{
    m_filesInDirectory.clear();
}

void FileSystem::setPointedAt(int index)
{
    if(!m_filesInDirectory.empty())
        m_filesInDirectory[index]->setPointed();
}

void FileSystem::dePointAt(int index)
{
    if(!m_filesInDirectory.empty())
        m_filesInDirectory[index]->dePoint();
}

void FileSystem::setSelectedAt(int index)
{
    if(!m_filesInDirectory.empty())
        m_filesInDirectory[index]->select();
}

void FileSystem::deSelectAt(int index)
{
    if(!m_filesInDirectory.empty())
        m_filesInDirectory[index]->deSelect();
}

int FileSystem::filesInCurrentDirectory()
{
    return m_filesInDirectory.size();
}

void FileSystem::copySelectedFiles(const fs::path &destination)
{
    for(const auto& file : m_filesInDirectory)
    {
        if(file->isSelected())
        {
            file->copy(destination);
        }
    }
    deSelectAllFiles();

}

void FileSystem::moveSelectedFiles(const fs::path &destination)
{
    for(const auto& file : m_filesInDirectory)
    {
        if(file->isSelected())
        {
            file->move(destination);
        }
    }
    deSelectAllFiles();
}

void FileSystem::removeSelectedFiles()
{
    for(const auto& file : m_filesInDirectory)
    {
        if(file->isSelected())
        {
            file->remove();
        }
    }
    deSelectAllFiles();
}

void FileSystem::deSelectAllFiles()
{
    for(const auto& file : m_filesInDirectory)
    {
        file->deSelect();
    }
}

void FileSystem::selectOnRegex(const std::regex &regexPattern)
{
    for(const auto& file : m_filesInDirectory)
    {
        file->selectOnRegex(regexPattern);
    }
}

void FileSystem::appendSelectedFilesTo(std::ofstream &outputFile)
{
    for(const auto& file : m_filesInDirectory)
    {
        if(file->isSelected())
        {
            file->appendContentsTo(outputFile);
        }
    }
}

void FileSystem::selectOnText(const std::string &text)
{
    for(const auto& file : m_filesInDirectory)
    {
        file->selectOnText(text);
    }
}

void FileSystem::deduplicateSelectedFileIn(fs::path &directoryToSearchIn)
{
    std::unique_ptr<File> originalFile(m_filesInDirectory[getSelectedFileIndex()]->clone());


    if(!originalFile)
        return;

    
    clearFileSystem();
    
    loadFiles(directoryToSearchIn);

    for(const auto& file : m_filesInDirectory)
    {
        if(file->isEqualTo(*originalFile))
        {
            file->changeToSymbolicLink(*originalFile);
        }
    }

}

void FileSystem::deduplicateSelectedFileInCurrentDirectory()
{
    std::unique_ptr<File> originalFile(m_filesInDirectory[getSelectedFileIndex()]->clone());
    m_filesInDirectory.erase(m_filesInDirectory.begin() + getSelectedFileIndex());

    if(!originalFile)
        return;
    
    for(const auto& file : m_filesInDirectory)
    {
        if(file->isEqualTo(*originalFile))
        {
            file->changeToSymbolicLink(*originalFile);
        }
    }

}

int FileSystem::selectedFilesCount()
{
    int count = 0;
    for(const auto& file : m_filesInDirectory)
    {
        if(file->isSelected())
        {
            count++;
        }
    }
    return count;
}

int FileSystem::getSelectedFileIndex()
{
    for(size_t i = 0; i < m_filesInDirectory.size(); i++)
    {
        if(m_filesInDirectory[i]->isSelected())
        {
            return i;
        }
    }
    throw std::runtime_error("No file selected");
}
