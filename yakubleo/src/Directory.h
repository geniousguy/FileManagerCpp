#pragma once
#include <filesystem>
#include <ncurses.h>
#include "File.h"
#include <fstream>

/**
 * @class Directory
 * @brief Class representing a directory, derived from the File class.
 *
 */
class Directory : public File 
{
public:
    /**
     * @brief Default constructor for the Directory class.
     */
    Directory()=default;

    /**
     * @brief Constructor for the Directory class with a directory path.
     * @param pathToFile The path to the directory.
     */
    Directory(const fs::path &pathToFile);


    /**
     * @brief Copies the directory.
     *
     */
    void copy(const fs::path &destination) override;

    /**
     * @brief Moves the directory.
     *
     */
    void move(const fs::path &destination) override;

    /**
     * @brief Removes the directory.
     *
     */
    void remove() override;

    /**
     * @brief Prints the directory name.
     *
     *
     * @param row The row number for printing.
     * @param column The column number for printing.
     * @param normalColour The color pair number for normal display.
     * @param selectedColour The color pair number for selected display.
     */
    void print(int row, int column, int normalColour, int selectedColour ) const override;

    /**
     * @brief Ignores the output file stream.
     */
    void appendContentsTo(std::ofstream& outputStream) const override;

    /**
     * @brief Ignores the text so that only regular files are selected.
     * @param text The text to match.
     */
    void selectOnText(const std::string &text) override;

    /**
     * @brief Clones the directory.
     * @return A pointer to the cloned directory.
     */
    File *clone() const override;

    /**
     * @brief Ignores the other file so that only regular files are selected.
     * @param otherFile The other file.
     * @return false.
     */
    bool isEqualTo(const File &otherFile) const override;

    /**
     * @brief Returns an empty string so that only regular files return contents.
     * @return Empty string.
     */
    std::string getContents() const override;

    /**
     * @brief Does nothing. So that only regular files can be changed to symbolic links.
     * @param fileToPointAt The file to point at.
     */
    void changeToSymbolicLink(const File& fileToPointAt) override;    

};