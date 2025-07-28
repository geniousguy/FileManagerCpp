#pragma once
#include <filesystem>
#include <ncurses.h>
#include "File.h"
#include <fstream>

/**
 * @class SymbolicLink
 * @brief Class representing a symbolic link, derived from the File class.
 *
 */
class SymbolicLink : public File 
{
public:
    /**
     * @brief Default constructor for the SymbolicLink class.
     */
    SymbolicLink()=default;

    /**
     * @brief Constructor for the SymbolicLink class with a symbolic link path.
     * @param pathToFile The path to the symbolic link.
     */
    SymbolicLink(const fs::path &pathToFile);

   

    /**
     * @brief Copies the symbolic link.
     *
     */
    void copy(const fs::path &destination) override;

    /**
     * @brief Moves the symbolic link.
     *
     */
    void move(const fs::path &destination) override;

    /**
     * @brief Removes the symbolic link.
     *
     */
    void remove() override;

    /**
     * @brief Prints the symbolic link name.
     *
     * This function prints the symbolic link name.
     *
     * @param row The row number for printing.
     * @param column The column number for printing.
     * @param normalColour The color pair number for normal display.
     * @param selectedColour The color pair number for selected display.
     */
    void print(int row, int column, int normalColour, int selectedColour ) const override;


    /**
     * Ignores the output file stream.
     */
    void appendContentsTo(std::ofstream& outputStream) const override;

    /**
     * @brief Ignores the text so that only regular files are selected.
     */
    void selectOnText(const std::string &text) override;

    /**
     * @brief Clones the symbolic link.
     *
     * This function clones the symbolic link.
     *
     * @return A pointer to the cloned symbolic link.
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
    void changeToSymbolicLink(const File &fileToPointAt) override;
};