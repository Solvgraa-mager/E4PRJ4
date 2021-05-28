<?php

include_once 'dbh.inc.php';

$Tempset = 0;
$Saltset = 0;
$Lightset = 0;

    if(isset($_POST['Temperatur'])){
        $Tempset = 1;
    }
    if(isset($_POST['Salt'])){
        $Saltset = 1;
    }
    if(isset($_POST['Lys'])){
        $Lightset = 1;
    }

    $sqlCmd = "UPDATE activeprocesses SET Temp = $Tempset, Salt = $Saltset, Light = $Lightset;";
    $result = $conn->query($sqlCmd);

    $conn->close();

    header("Location: ../homepage.php");
