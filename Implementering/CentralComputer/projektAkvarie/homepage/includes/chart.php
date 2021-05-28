<?php

include_once 'dbh.inc.php';

$sqlCMD = "SELECT * from measurements ORDER BY dateTime DESC LIMIT 96";
$result = mysqli_query($conn, $sqlCMD);
$chart_data = '';
while($row = mysqli_fetch_array($result))
{
 $chart_data .= "{ dateTime:'".$row["dateTime"]."', temp:".$row["temp"].", waterLevel:".$row["waterLevel"].", salt:".$row["salt"].", pH:" . $row["pH"]."}, ";
}
$chart_data = substr($chart_data, 0, -2);