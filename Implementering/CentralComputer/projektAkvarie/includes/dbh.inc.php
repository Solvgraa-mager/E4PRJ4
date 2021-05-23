<?php //because the file only contains php functionality, we dont have to end the document with the closing php tag

$dbServerName = "localhost"; // because the db is local and not online
$dbUserName = "phpadmin";
$dbPassword = "raspberry";
$dbName = "Akvariereg";

$conn = mysqli_connect($dbServerName, $dbUserName, $dbPassword, $dbName);