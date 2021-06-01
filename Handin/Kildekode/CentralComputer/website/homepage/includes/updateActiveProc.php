<?php

include_once 'dbh.inc.php';

// declares variables used in SQL-command
$Tempset = 0;
$Saltset = 0;
$Lightset = 0;

    //checks if checkboxes is set or not from homepage
    if(isset($_POST['Temperatur'])){
        $Tempset = 1;
    }
    if(isset($_POST['Salt'])){
        $Saltset = 1;
    }
    if(isset($_POST['Lys'])){
        $Lightset = 1;
    }

    // updates table 'avtiveprocesses' if the 
    $sqlCmd = "UPDATE activeprocesses SET Temp = $Tempset, Salt = $Saltset, Light = $Lightset;";
    $result = $conn->query($sqlCmd);

    $conn->close();

    //redirects to homepage
    header("Location: ../homepage.php");
