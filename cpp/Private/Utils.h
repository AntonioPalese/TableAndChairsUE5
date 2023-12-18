#pragma once

#include <string>
#include <iostream>
#include <filesystem>
#include <regex>
#include <cstdlib>

namespace fs = std::filesystem;

class utilities {

public:
    static void _flush( const std::string& path ) {
        try {
            // Iterate over the files in the directory
            for ( const auto& entry : fs::directory_iterator( path ) ) {
                // Check if the entry is a regular file
                if ( fs::is_regular_file( entry.path() ) ) {
                    // Remove the file
                    fs::remove( entry.path() );                    
                }
            }
        }
        catch ( const fs::filesystem_error& e ) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }


    static std::string get_available_name() {
        const std::string path = "C:\\code\\MyGit\\TableAndChairsUE5\\builder_files";
        std::string name;
        for ( const auto & entry : fs::directory_iterator( path ) ) {
            std::cout << entry.path() << std::endl;
            name = entry.path().filename().u8string();
        }
        if ( name.empty() ) {
            name = path + std::string( "\\" ) + std::string( "file1.txt" );
        }
        else {
            int idx;
            std::smatch match;
            if ( std::regex_search( name, match, std::regex( "\\d+" ) ) ) {
                idx = std::stoi( match.str() );
                name = path + std::string("\\") + std::regex_replace( name, std::regex( "\\d+" ), std::to_string( idx + 1 ) );
            }
            else
                exit( EXIT_FAILURE );
        }
        return name;
    }

    static bool exec() {
        const char* pythonScript = "C:\\code\\MyGit\\TableAndChairsUE5\\draw_from_file.py";

        std::string command = "conda activate nvtorch & call python " + std::string( pythonScript );

        
        int result = std::system( command.c_str() );

        if ( result == 0 ) {
            return true;
        }
        else {
            return false;
        }
    }
};