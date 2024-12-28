/* styles.css */

body {
    font-family: Arial, sans-serif;
    margin: 0;
    padding: 0;
    background-color: #f4f4f4;
    color: #333;
}

header {
    background-color: #4CAF50; /* Green background for the header */
    color: white;
    text-align: center;
    padding: 20px;
}

header h1 {
    margin: 0;
    font-size: 2.5em;
}

header p {
    font-size: 1.2em;
}

.content {
    padding: 20px;
    max-width: 1200px;
    margin: 0 auto;
    background-color: #e8f5e9; /* Light green background for the content */
    border-radius: 8px;
    box-shadow: 0 2px 5px rgba(0, 0, 0, 0.1);
}

.algorithm {
    margin-bottom: 30px;
    padding: 20px;
    background-color: white;
    border-radius: 5px;
    box-shadow: 0 2px 5px rgba(0, 0, 0, 0.1);
}

.algorithm h2 {
    font-size: 1.8em;
    color: #4CAF50;
    margin-bottom: 10px;
}

.algorithm ul {
    list-style-type: square;
    margin-left: 20px;
}

.algorithm a {
    color: #4CAF50;
    text-decoration: none;
}

.algorithm a:hover {
    text-decoration: underline;
}

table {
    width: 100%;
    border-collapse: collapse;
    margin-top: 20px;
}

table th, table td {
    padding: 12px;
    text-align: left;
    border-bottom: 1px solid #ddd;
}

table th {
    background-color: #f2f2f2;
}

footer {
    background-color: #333;
    color: white;
    text-align: center;
    padding: 10px;
    position: fixed;
    width: 100%;
    bottom: 0;
}

/* Styling for the code link */
.code-link a {
    color: #4CAF50;
    text-decoration: none;
    font-weight: bold;
}

.code-link a:hover {
    text-decoration: underline;
}
