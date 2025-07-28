#pragma once
#include <filesystem>
#include <ncurses.h>
#include "File.h"

/**
 * @class RegularFile
 * @brief Class representing a regular file, derived from the File class.
 *
 * The RegularFile class represents a regular file and is derived from the File class.
 */
class RegularFile : public File 
{
public:
    /**
     * @brief Default constructor for the RegularFile class.
     */
    RegularFile()=default;

    /**
     * @brief Constructor for the RegularFile class with a file path.
     * @param pathToFile The path to the file.
     */
    RegularFile(const fs::path &pathToFile);

    

    /**
     * @brief Copies the regular file.
     *
     * This function copies the regular file.
     */
    void copy(const fs::path &destination) override;

    /**
     * @brief Moves the regular file.
     *
     * This function moves the regular file.
     */
    void move(const fs::path &destination) override;

    /**
     * @brief Removes the regular file.
     *
     * This function removes the regular file.
     */
    void remove() override;

    /**
     * @brief Prints the regular file name.
     *
     * This function prints the regular file name.
     *
     * @param row The row number for printing.
     * @param column The column number for printing.
     * @param normalColour The color pair number for normal display.
     * @param selectedColour The color pair for number selected display.
     */
    void print(int row, int column, int normalColour, int selectedColour) const override;

    /**
     * @brief Appends the contents of the regular file to the output stream.
     *
     * @param outputStream The output stream to append the contents of the regular file to.
     */
    void appendContentsTo(std::ofstream& outputStream) const override;

    /**
     * @brief Selects the regular file if the file contents match the text.
     *
     * @param text The text to match the file contents against.
     */
    void selectOnText(const std::string &text) override;

    /**
     * @brief Clones the regular file.
     *
     * This function clones the regular file.
     *
     * @return A pointer to the cloned regular file.
     */
    File *clone() const override;

    /**
     * @brief Compares the regular file to another file.
     *
     * @param otherFile The other file to compare the regular file to.
     * @return True if the regular file is equal to the other file, false otherwise.
     */
    bool isEqualTo(const File &otherFile) const override;

    /**
     * @brief Gets the contents of the regular file.
     *
     * @return The contents of the regular file.
     */
    std::string getContents() const override;

    /**
     * @brief Changes the regular file to a symbolic link.
     *
     * @param fileToPointAt The file to point the symbolic link to.
     */
    void changeToSymbolicLink(const File &fileToPointAt) override;
};