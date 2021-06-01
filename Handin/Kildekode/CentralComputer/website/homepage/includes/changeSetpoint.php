<?php

include_once 'dbh.inc.php';

// reads global variables from homepage.php
$setpointValue = $_POST['setValue'];
$setpointParam = $_POST['parameter'];

// validate values send from user and update setpoints by SQL-command "UPDATE 'table' SET..."
// ignores unsupported values.

if($setpointParam == 'Temp'){
    if($setpointValue >= 21 && $setpointValue <= 30){ //jævnfør krav
        $sqlCmd = "UPDATE setpoints SET $setpointParam = '$setpointValue';";
        $result = $conn->query($sqlCmd);
        $conn->close();

        print "Setpoint updated succesfully.\n";
    }
}
elseif($setpointParam == 'Waterlevel'){
    if($setpointValue >= 22 && $setpointValue <= 28){ //jævnfør krav
        $sqlCmd = "UPDATE setpoints SET $setpointParam = '$setpointValue';";
        $result = $conn->query($sqlCmd);
        $conn->close();

        print "Setpoint updated succesfully.\n";
    }
}
elseif($setpointParam == 'Salt'){
    if($setpointValue >= 31.5 && $setpointValue <= 38.5){ //jævnfør krav
        $sqlCmd = "UPDATE setpoints SET $setpointParam = '$setpointValue';";
        $result = $conn->query($sqlCmd);
        $conn->close();

        print "Setpoint updated succesfully.\n";
    }
}
else
{
    if($setpointValue >= 0 && $setpointValue <= 1){
        $sqlCmd = "UPDATE setpoints SET $setpointParam = '$setpointValue';";
        $result = $conn->query($sqlCmd);
        $conn->close();
    }
}
    // redirects back to homepage
    header("Location: ../homepage.php");
