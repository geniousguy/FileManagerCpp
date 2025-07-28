#pragma once
#include <filesystem>
#include <ncurses.h>
#include <regex>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

/**
 * @class File
 * @brief Parent class for multiple file types.
 * 
 */
class File 
{
public:
    /**
     * @brief Default constructor for the File class.
     */
    File()=default;

    /**
     * @brief Constructor for the File class with a file path.
     * @param pathToFile The path to the file.
     */
    File(const fs::path &pathToFile);

    /**
     * @brief Selects the file.
     *
     * This function toggles the selection status of the file.
     */
    void select();

        
    /**
     * @brief Deselects the file.
     *
     * This function sets the selection status of the file to false.
     */
    void deSelect();

    /**
     * @brief Sets the file as pointed.
     *
     * This function marks the file as pointed at.
     */
    void setPointed();

    /**
     * @brief Clears the pointed status of the file.
     *
     * This function removes the pointed status of the file.
     */
    void dePoint();

    /**
     * selects the file if the file name matches the regular expression
    */
    void selectOnRegex(const std::regex &regularExpression);

    /**
     * @brief Gets the file name.
     * @return The file name.
     */
    std::string getName() const;

    /**
     * @brief Gets the file path.
     * @return The file path.
     */
    fs::path getPath() const;

    /**
     * @brief Copies the file.
     *
     * This pure virtual function is to be implemented by derived classes to copy the file.
     */
    virtual void copy(const fs::path &destination) = 0;

    /**
     * @brief Moves the file.
     *
     * This pure virtual function is to be implemented by derived classes to move the file.
     */
    virtual void move(const fs::path &destination) = 0;

    /**
     * @brief Removes the file.
     *
     * This pure virtual function is to be implemented by derived classes to remove the file.
     */
    virtual void remove() = 0;

    /**
     * @brief Prints the file information.
     *
     * This pure virtual function is to be implemented by derived classes to print the file information.
     *
     * @param row The row number for printing.
     * @param column The column number for printing.
     * @param normalColour The color pair number for normal display.
     * @param selectedColour The color pair number for selected display.
     */
    virtual void print(int row, int column, int normalColour, int selectedColour ) const = 0;

    /**
     * @brief Appends the contents of the file to the output stream.
     *
     * This pure virtual function is to be implemented by derived classes to append the contents of the file to the output stream.
     *
     * @param outputStream The output stream to append the contents of the file to.
     */
    virtual void appendContentsTo(std::ofstream& outputStream) const = 0;

    /**
     * @brief Selects the file if the file contents match the text.
     *
     * This pure virtual function is to be implemented by derived classes to select the file if the file contetns match the text.
     *
     * @param text The text to match.
     */
    virtual void selectOnText(const std::string &text) = 0;

    /**
     * @brief Clones the file.
     * @return A pointer to the cloned file.
    */
    virtual File *clone() const = 0;

    /**
     * @brief Tells if the file is equal to other file.
     * @param otherFile The other file to compare to.
     * @return True if the file is equal to other file, false otherwise.
     */
    virtual bool isEqualTo(const File &otherFile) const = 0;

    /**
     * @brief Gets the contents of the file.
     * @return The contents of the file.
     */
    virtual std::string getContents() const = 0;

    /**
     * @brief Changes a regular file to a symbolic link.
     */
    virtual void changeToSymbolicLink(const File& fileToPointAt) = 0;    

    /**
     * @brief Virtual destructor for the File class.
     */
    virtual ~File() = default;

    /**
     * @brief Checks if the file is selected.
     * @return True if the file is selected, false otherwise.
     */
    bool isSelected() const;
protected:
    fs::path m_pathToFile; /**< The path to the file. */
    bool m_isSelected; /**< The selection status of the file. */
    bool m_isPointedAt; /**< The pointed status of the file. */
};



