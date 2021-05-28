<?php

include_once "dbh.inc.php";

$startTimeStamp = $_POST['startTimeStamp'];
$endTimeStamp = $_POST['endTimeStamp'];

$select = "SELECT * FROM measurements WHERE dateTime >= '{$startTimeStamp}' AND dateTime <= '{$endTimeStamp}'"; //mysql command
$result = $conn->query($select);

if($result->num_rows > 0){
    $delimiter = ",";
    $filename = "measurements.csv";

    //create file pointer
    $f = fopen('php://memory', 'w');

    //set colum headers
    $fields = array('Temperatur', 'Vandniveau', 'Saltindhold', 'pH', 'Tidspunkt');
    fputcsv($f, $fields, $delimiter);

    //output each row of the data, format the lines as csv and put it into the filepointer $f
    while($row = $result->fetch_assoc()){
        $lineData = array($row['temp'], $row['waterLevel'], $row['salt'], $row['pH'] , $row['dateTime']);
        fputcsv($f, $lineData, $delimiter);
    }
    //move back to the beginning og file
    fseek($f, 0);

    //set headers to download file rather than displayed
    header('Content-Type: text/csv');
    header('Content-Disposition: attachment; filename="' . $filename . '";');

    //output all remaining data on a file pointer
    fpassthru($f);

}
exit;
fclose($fp);
$conn->close();