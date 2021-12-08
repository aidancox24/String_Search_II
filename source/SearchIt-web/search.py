from flask import Flask, render_template, request, json

import subprocess

app = Flask(__name__)

# The name of our search executable used to search for patterns
SEARCH_EXE = "SearchIt.exe"


# The main page of our search web app
@app.route("/")
def index():
    return render_template('search-home.html')


# The page that shows the search results
@app.route("/search_results", methods = ['POST'])
def do_post_search():
    
    # Get the pattern the user wants to search form
    pattern = request.form.get('pattern')
    
    # Get the type of search (KMP or BM) the user wants to use for their search
    searchType = request.form.get('searchType')

    # Get the text we want to search through
    text = request.form.get('txt');
    
    # f = request.files['searchFile']
    # f.save(f.filename)

    # Execute the search using our search cli
    # Capture the output since we know our search exe gives a search summary in the output
    # outputSummary = subprocess.run([SEARCH_EXE, f.filename, pattern, searchType], capture_output=True, text=True).stdout
    outputSummary = subprocess.run([SEARCH_EXE, searchType, pattern, text], capture_output=True, text=True).stdout

    # Now show our search results page (we are passing that page the search "summary" data)
    return render_template('search-results.html', summary=outputSummary, pattern=pattern, matches=text)


# With this code here, you can simply just do "python search.py" on your commandline
# Otherise you do "python -m flask run"
if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0')