<img src="./images/URI.png" width="64" align="right">

# CSC212 Fall 2021 Project - String Search II

Our project focuses on 2 search alogrithms listed below. You can find much more details about our findings and project results in our [Project Report](https://github.com/aidancox24/String_Seach_II/tree/main/project-report). Also check out our [Project Slides](https://github.com/aidancox24/String_Seach_II/tree/main/project-report) for a nice overview of our project.

- Knuth-Morris-Pratt Algorithm
- Boyer-Moore-Algorithm

<p><hr/></p>

This readme provides more information about our code structure, coding implementation, application demos, how to build and links to all available resources related to our project.

# Project Team (Team #18)

<img src="./images/Project-Team.jpg" width="700" style="padding-bottom: 20px">

# Individual Contributions

<p style="color: red">Info here to be finalized.......</p>

**Aidan Cox** - Search C++ Class implementation, Windows GUI App implementation, Web App implementation, project slides, Github/Readme.md

**Nicholas Mendes** - KMP C++ implementation, BM C++ implementation, project slides, ...

**Emily Lavoie** - Project Report, project slides

**Bilguuntur Munkhzaya** - algorithm plotting and visuals, project slides


# Quick Links

Here is some quick access to a list of available project-related resources for download.

[Project Report](https://github.com/aidancox24/String_Seach_II/tree/main/project-report)

[Project Presentation Slides](https://github.com/aidancox24/String_Seach_II/tree/main/Presentation)

[Source Code Files](https://github.com/aidancox24/String_Seach_II/tree/main/source) 

[Search CLI executable](https://github.com/aidancox24/String_Seach_II/blob/main/downloads/SearchIt.exe) 

[Search Windows GUI](https://github.com/aidancox24/String_Seach_II/blob/main/downloads/SearchIt-app.exe)

[Search Web Application (demo video)](http://github.com/fooo)


# Application Demos

In addition to the implementation of our Search class and algorithm implementations, we decided to create 3 separate applications to show how we could use a common base of search code, and use it in 3 different application technologies:

- Command Line Interface (CLI)
- Windows-based GUI
- Web-based GUI

The following sections provides details on how to run these applications.

## Command Line Interface (Demo)
This is our main application which has **ALL** of our search logic and search algorithm implementations.

To run this CLI demo, first download our [Search CLI executable](https://github.com/aidancox24/String_Seach_II/blob/main/downloads/SearchIt.exe) to a directory on your system and then open a terminal window. Follow the instructions below to demo it.

--> To see the usage info for our search command line issue this command:

```
$ searchIt -h
```

Ouput:

```
Usage:
        searchit.exe [searchType] [searchPattern] [text | fileName -file]

        Arguments:
                [searchType] - KMP or BM
                [searchPattern] - text pattern to search
                [text | fileName -file] - text or a filename that has text

        Examples:
                # Use the KMP algorithm to search for 'AABA' in the text 'ABCAABACDBABABABBA'
                search.exe KMP AABA ABCAABACDBABABABBA

                # Use the BM algorithm to search for 'AABA' in the file sample.txt'
                search.exe KMP AABA sample.txt -file
```

--> To search for a pattern in a simple string, using the Knuth-Morris-Pratt algorith, issue this command:

```
$ searchIt KMP URI UUUURIIURIUURIURIIURIIIUURIRRURII
```
Ouput:
```
* * * Knuth Morris Pratt Search Algorithm * * *

Search Duration:      401 milliseconds
Search Pattern:       URI
Search Results File:  URI-SEARCH-RESULTS-KMP.txt
Search Results:
        "URI" found at index 3
        "URI" found at index 7
        "URI" found at index 11
        "URI" found at index 14
        "URI" found at index 18
        "URI" found at index 24
        "URI" found at index 29

```

--> To search for a pattern using the Boyer-Moore-Algorithm, issue this command:

```
$ searchIt BM URI UUUURIIURIUURIURIIURIIIUURIRRURII
```
Ouput:
```
* * * Boyer Moore Search Algorithm * * *

Search Duration:      508 milliseconds
Search Pattern:       URI
Search Results File:  URI-SEARCH-RESULTS-.txt
Search Results:
        "URI" found at index 3
        "URI" found at index 7
        "URI" found at index 11
        "URI" found at index 14
        "URI" found at index 18
        "URI" found at index 24
```

--> To search for a pattern from text loaded from a **file** issue this command:

```
$ searchIt BM URI sample.txt -file
```
Ouput:
```
* * * Boyer Moore Search Algorithm * * *

Search Duration:      600 milliseconds
Search Pattern:       URI
Search Results File:  URI-SEARCH-RESULTS-.txt
Search Results:
        "URI" found at index 3
        "URI" found at index 7
        "URI" found at index 11
        "URI" found at index 14
        "URI" found at index 18
        "URI" found at index 24
```

## Windows-based GUI (Demo)

In addition to our CLI application, we wanted to create a Windows-based GUI which utilizes our search algorithms. 

To run this GUI demo, download our [Search App executable](https://github.com/aidancox24/String_Seach_II/blob/main/downloads/SearchIt-app.exe) to a directory on your system. Double click to launch the application. You should see the following:

<img src="./images/SearchIt-app.png" width="300" style="padding-bottom: 20px">

--> You can now interact with our search GUI to do things such as:
- Enter a pattern
- Manually enter text to search OR
- Load text from a file
- Search using Knuth-Morris-Pratt OR Boyer-Moore-Algorithm

Sample Output:

<img src="./images/SearchIt-app-example.png" width="300" style="padding-bottom: 20px">


## Windows-based GUI (Demo)

We also created a third GUI to demonstrate how we could call into our search algorithms from a web browser! Setting up this web environment is a little much for a quick demo. See the How to Build section if you want to setup the environment for yourself. So we are showing you some screenshots here

--> You can interact with our web-based search GUI from your favorite browser and do things such as:

- Enter a pattern
- Manually enter text to search OR
- Load text from a file
- Search using Knuth-Morris-Pratt OR Boyer-Moore-Algorithm

<img src="./images/SearchIt-web.png" width="500" style="padding-bottom: 20px">

Sample Output:
- Note how we added some javascript logic to also highlight the matched patterns!
  
<img src="./images/SearchIt-web-results.png" width="500" style="padding-bottom: 20px">


# Building the Source Code

You may want to build our search source code for yourself. This section describes the steps and dependencies.

## Command Line Interface (Build)

Building our main source code for our search app is pretty straight foward.

-> Download the searchit.cpp and searchit.h from our [source](https://github.com/aidancox24/String_Seach_II/tree/main/source/SearchIt-cli) directory.

-> Open a terminal to where you saved the files.

-> Execute the following command to build and create the search executable:

```
$ g++ -o search.exe searchit.cpp searchit.h
```
For usage instructions you can now run your exe like this:

```
$ search.exe -h 

Usage:
        searchit.exe [searchType] [searchPattern] [text | fileName -file]

        Arguments:
                [searchType] - KMP or BM
                [searchPattern] - text pattern to search
                [text | fileName -file] - text or a filename that has text (use -file when specifying a                                                                   filename)

        Examples:
                # Use the KMP algorithm to search for 'AABA' in the text 'ABCAABACDBABABABBA'
                search.exe KMP AABA ABCAABACDBABABABBA

                # Use the BM algorithm to search for 'AABA' in the file sample.txt'
                search.exe KMP AABA sample.txt -file

```

## Windows-based GUI (Demo)

Building our Windows-based GUI involves installing the [C++ Builder IDE](https://www.embarcadero.com/products/cbuilder/starter/free-download) and setting up your environment a bit. See our [README.md](https://github.com/aidancox24/String_Seach_II/blob/main/source/SearchIt-app/README.md) which is dedicated in the steps on getting your environment setup to build the Windows-based search app.

## Web-based GUI (Build)

For our Web-based GUI, you really don't "build" the GUI but rather just run it. We use the Flask/Python environment that lets you simply use python to accept web requsts, do some work, then respond with the html/js.  Here is a good tutorial on this.

To get your environment setup, simply follow these instructions.

-> Install the latest version of Python on your system

-> Create a project folder to store our web files.

-> From with your project folder issue this command to create a virtual env

```
py -3 -m venv .venv
```

-> Activate your new virtual env

```
.venv\scripts\activate
```

-> Make sure pip is installed

```
python -m pip install --upgrade pip
```

--> Install the Flask module which is required to simulate a web server

```
python -m pip install flask
```
-> Run your search.py program which starts the Flask/Python webserver on port 5000.

```
py search.py
```

Ouput:

```
 * Serving Flask app 'search' (lazy loading)
 * Environment: production
   WARNING: This is a development server. Do not use it in a production deployment.
   Use a production WSGI server instead.
 * Debug mode: on
 * Restarting with stat
 * Debugger is active!
 * Debugger PIN: 780-911-110
 * Running on all addresses.
   WARNING: This is a development server. Do not use it in a production deployment.
 * Running on http://localhost:5000/ (Press CTRL+C to quit)
```
-> Open a browser to http://localhost:5000 to use the search web application!

# Project Report

You can download our [Project Report](https://github.com/aidancox24/String_Seach_II/tree/main/project-report) to get details about our project findings.