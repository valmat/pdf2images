#include <iostream>
#include "check_create.h"


std::optional<pdf::Pdf> check_create(const std::string& inp_file) noexcept
{
    if(!pdf::Pdf::is_pdf_fext(inp_file)) {
        std::cerr << "File " << inp_file << " is not a PDF document." << std::endl; 
        return {};
    }

    // pdf::Pdf doc(inp_file);
    std::optional<pdf::Pdf> doc{std::in_place, inp_file};


    if(!doc->is_valid()) {
        std::cerr << "Failed to read the PDF file " << inp_file << std::endl; 
        return {};
    }

    if(!doc->is_pdf()) {
        std::cerr << "File " << inp_file << " is not a PDF document." << std::endl; 
        return {};
    }    

    if (doc->is_locked()) {
        std::cerr << "Locked document " << inp_file << std::endl; 
        return {};
    }
    if (doc->is_encrypted()) {
        std::cerr << "Encrypted document " << inp_file << std::endl; 
        return {};
    }

    return doc;
}
