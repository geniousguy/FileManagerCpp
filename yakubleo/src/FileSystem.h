#pragma once
#include <vector>
#include <memory>
#include <filesystem>
#include <ncurses.h>
#include "Directory.h"
#include "RegularFile.h"
#include "SymbolicLink.h"
#include <regex>



namespace fs = std::filesystem;
/**
 * @class FileSystem
 * @brief Represents a file system containing directories and files.
 */
class FileSystem
{
public:
    /**
     * @brief Constructs a FileSystem object with the given directory path.
     * @param directory The path to the directory.
     */
    FileSystem(const fs::path &directory);

    /**
     * @brief Prints the files in the file system.
     * @param initialRow The initial row position for printing.
     * @param initialColumn The initial column position for printing.
     * @param normalFileColourPair The color pair number for normal files.
     * @param selectedFileColourPair The color pair number for selected files.
     */
    void print(int initialRow, int initialColumn, int normalFileColourPair, int selectedFileColourPair, int printFrom, size_t totalLinesInTerminal) const;

    /**
     * @brief Loads the files from the specified directory.
     * @param directory The path to the directory.
     */
    void loadFiles(const fs::path &directory);

    /**
     * @brief Clears the file system by removing all files.
     */
    void clearFileSystem();

    /**
     * @brief Sets the pointed-at state for the file at the specified index.
     * @param index The index of the file to set the pointed-at state.
     */
    void setPointedAt(int index);

    /**
     * @brief Clears the pointed-at state for the file at the specified index.
     * @param index The index of the file to clear the pointed-at state.
     */
    void dePointAt(int index);

    /**
     * @brief Sets the selected state for the file at the specified index.
     * @param index The index of the file to set the selected state.
     */
    void setSelectedAt(int index);

    /**
     * @brief Clears the selected state for the file at the specified index.
     * @param index The index of the file to clear the selected state.
     */
    void deSelectAt(int index);

    /**
     * @brief Returns the number of files in the current directory as an integer
    */
    int filesInCurrentDirectory();

    /**
     * @brief Copies the selected files to the specified directory, de selects all files after that.
     * @param destination The destination directory to copy the files to.
     */
    void copySelectedFiles(const fs::path &destination);

    /**
     * @brief Moves the selected files to the specified directory, de selects all files after that.
     * @param destination The destination directory to move the files to.
     */
    void moveSelectedFiles(const fs::path &destination);

    /**
     * @brief Removes the selected files, de selects all files after that.
     */
    void removeSelectedFiles();

    /**
     * @brief Sets the selected state for all files to false.
     */
    void deSelectAllFiles();

    /**
     * @brief Selects all files that match the regex pattern.
     */
    void selectOnRegex(const std::regex &regexPattern);

    /**
     * @brief Appends the selected file contents to the specified output file.
     * @param outputFile The output file to append the contents to.
     */
    void appendSelectedFilesTo(std::ofstream &outputFile);

    /**
     * @brief Selects the files with the specified text in its contents.
     * @param text The text to search for.
     */
    void selectOnText(const std::string &text);


    void deduplicateSelectedFileIn(fs::path &directoryToSearchIn);


    void deduplicateSelectedFileInCurrentDirectory();

    /**
     * @brief Returns the number of selected files as an integer.
     */
    int selectedFilesCount();


    int getSelectedFileIndex();


private:
    std::vector<std::unique_ptr<File>> m_filesInDirectory; /**< The files in the current directory. */
};