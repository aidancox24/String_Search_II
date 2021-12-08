/** Some custom javascript for our search web app */

/**
 * Validates the pattern making sure there is a value - show a error message
 */
function validatePattern() {

    // Hide or show the error messages that ask for pattern
    let isPatternEmpty = document.getElementById("pattern").value.length < 1;

    document.getElementById("patternError").hidden = !isPatternEmpty;

    // Return true is all is good
    return !isPatternEmpty;
}

/**
 * Validates the text making sure there is a value - show a error message
 */
function validateText() {

    // Hide or show the error messages that ask for text
    let isTextEmpty = document.getElementById("file-preview").value.length < 1;

    document.getElementById("textError").hidden = !isTextEmpty;

    // Return true is all is good
    return !isTextEmpty;
}

/**
 * Validates both the pattern and text making sure they have values
 */
function validateInput() {

    let patterOK = validatePattern();
    let textOK = validateText();

    // Return true if both patter and text is ok
    return patterOK && textOK;
}


/**
 * Handles the event after the user selects a file in the open file dialog.
 * Display the selected file in the text area.
 */
function loadSearchText() {

    var reader = new FileReader();

    // Get the name of the file just selected in the dialog
    var file = document.getElementById("searchFile").files[0];

    // Create a function that will handle when the file is read...so we can put the text in the preview text area
    reader.onload = function (e) {
        var textArea = document.getElementById("file-preview");
        textArea.value = e.target.result;

    };

    // Read the file and put the text in the preview text area
    reader.readAsText(file);

    // Show the file size right under the text area
    //document.getElementById("file-size").innerHTML = "File size: " + file.size + " bytes"
}

function showMatches() {

    // Get the pattern we searched for
    var pattern = document.getElementById("pattern").innerHTML;

    // Get the text in the matchces text area
    var matchesTextArea = document.getElementById("matches");
    var text = document.getElementById("matches").innerText;

    // Using RegEx to quickly find and highlight the matched pattern in our string
    let substring = new RegExp(pattern, "gi");

    var replaceStr = text.replace(substring, (match) => {
        // Surround all matches with html "mark" (yellow highlight)
        return `<mark>${match}</mark>`;
    });
     
    // Replace the text with the new marked up text
    matchesTextArea.innerHTML = replaceStr;
    
}