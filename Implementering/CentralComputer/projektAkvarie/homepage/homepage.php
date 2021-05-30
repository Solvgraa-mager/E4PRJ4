<!--This whole projekt "ProjektAkvarie" is part of E4PRJ4 at Aarhus University.
The project is build of HTML, PHP and CSS. These files can be found at same
directory as this doc.
Since E-students have'nt had any teching in web development and GUI, knowlegde have been
found mainly at w3schools.com.
Notice that the php-scripts is being executed at server-site and won't be readable for user,
unless the function "echo" is being used.

Authers: David Vestergaard and Christian Schultz -->

<?php
//database connection
require("includes/dbh.inc.php");
// include chart to acess variables
require("includes/chart.php");
?>

<!DOCTYPE html>
<html>
<head>
    <title>Akvarieregulator</title>
    <!-- local styles -->
    <link rel="stylesheet" href="style.css">
    <!-- styles for chart header. chart implementation is inspired from https://www.lisenme.com/create-charts-graphs-using-mysql-php-morris-js-tutorial/ -->
    <link rel="stylesheet" href="//cdnjs.cloudflare.com/ajax/libs/morris.js/0.5.1/morris.css">
    <script src="//ajax.googleapis.com/ajax/libs/jquery/1.9.0/jquery.min.js"></script>
    <script src="//cdnjs.cloudflare.com/ajax/libs/raphael/2.1.0/raphael-min.js"></script>
    <script src="//cdnjs.cloudflare.com/ajax/libs/morris.js/0.5.1/morris.min.js"></script>

</head>
<body>
    <!--main class: overall style -->
    <div class = "mainContainer">

<h1> Velkommen til Akvarieregulator </h1>
<div class = "wrapper_blade" >
<div class = "userInputs">
    <!-- ************* "Indstil setpoints" *********** -->
<h2>Indstil setpoints</h1>
<table>
<?php
    // SQL-command request send to database.
    $sql = "SELECT Temp, Waterlevel, Salt, Light FROM setpoints";
    // sends the request
    $result = $conn->query($sql);
    if ($result->num_rows > 0) {
    // output (using echo) data from each row until it reaches an empty row
        while($row = $result->fetch_assoc()) {
        echo "<tr><td>Setpoint for temperatur: " . "<b>" . $row["Temp"] . " C°</b></td></tr><tr><td>Setpoint for vandniveau: " . "<b>" .  $row["Waterlevel"] . " cm</b></td></tr><tr><td>Setpoint for salt: " . "<b>"
        . $row["Salt"] . " PSU</b></td></tr><tr><td>Setpoint for lys: " . "<b>" . $row['Light'] . "</b></td></tr>";}
        echo "</table>";
    }
    else { echo "0 results"; }
?>
</table>

<p>Vælg parameter du ønsker at ændre setpoint på.</p>
<!-- This is a form. The "action" will be called when the "submit" is pressed by user. -->
<form method = "POST" action = "includes/changeSetpoint.php">
  <label for="setpointParam">Vælg en parameter:</label>
  <select name="parameter" id="setpointParam">
    <option value="Temp">Temperatur</option>
    <option value="Waterlevel">Vand Niveau</option>
    <option value="Salt">Salt</option>
    <option value="Light">Lys</option>
  </select>
  <br><br>

  <label for="value">Indtast ønsket set-værdi:</label>
  <input type= "text" name = "setValue" placeholder = "Indtast værdi" id = "value">
  <br><br>
  <input type="submit" value="Opdatér setpoint">
</form>
</div>

<!-- *********** Aktive reguleringsprocessor ********** -->

<div class = "userInputs">
<h2>Aktive reguleringsprocessor</h1>
<p> Check/uncheck paramtre, der ønskes værende aktive/passive.</p>
<form action="includes/updateActiveProc.php" method = "post">

<?php
// SQL-command to get acess to data from table "activeprocesses"
$result = $conn->query("SELECT Temp, Salt, Light FROM activeprocesses");

// checks if the data is set to 1, if? then the checkbox is set to "checked"
// This indicates if the regulation is running or not
while($row = $result->fetch_assoc()){
    if($row['Temp'] == 1){
        echo '<input type="checkbox" id="temp" name="Temperatur" value="temp" checked>';
    }
    else{
        echo '<input type="checkbox" id="temp" name="Temperatur" value="temp">';
    }
    echo '<label for="temp"> Aktivér temperaturregulering</label><br>';
    if($row['Salt']== 1){
        echo '<input type="checkbox" id="salt" name="Salt" value="salt" checked>';
    }
    else{
        echo '<input type="checkbox" id="salt" name="Salt" value="salt">';
    }
    echo '<label for="salt"> Aktivér saltregulering  </label><br>';
    if($row['Light'] == 1){
        echo '<input type="checkbox" id="light" name="Lys" value="lys" checked>';
    }
    else{
        echo '<input type="checkbox" id="light" name="Lys" value="lys">';
    }
    echo '<label for="light"> Aktivér lys</label><br><br>';
    echo '<input type="submit" value="Opdatér processor">';
}
?>
</form>
</div>

<!-- *********** Download måledata ************* -->

<div class = "userInputs">
<h2>Download måledata</h1>

<p>Vælg ønsket start- og sluttidspunkt og tryk på 'Gem Data'.</p>

<form method= 'POST' action = "includes/download.php">
    <label for = "startTimeStamp">Vælg ønsket start-tidspunkt:</label>
    <select id = "startTimeStamp" name = "startTimeStamp">
<?php

$result = $conn->query("SELECT dateTime FROM measurements");

//displays all measurements and turn them into an option.
while($row = $result->fetch_assoc()){
    echo '<option value="' . $row['dateTime'] . '">'. $row['dateTime'] .'</option>';
}
?>
</select>

<br> <br>
    <label for = "endTimeStamp">Vælg ønsket slut-tidspunkt:</label>
    <select id = "endTimeStamp" name = "endTimeStamp">

<?php
    $result = $conn->query("SELECT dateTime FROM measurements ORDER BY dateTime DESC");

    //displays all measurements and turn them into an option.
    while($row = $result->fetch_assoc()){
        echo '<option value="' . $row['dateTime'] . '">'. $row['dateTime'] .'</option>';}
?>
</select>
<br> <br>
<input type = 'submit' value = 'Gem Data' name = 'Download'>
</form>
    </div>

<!-- *********** Seneste måling ************* -->

    <div class = "userInputs">
        <h2>Seneste måling </h2>
<?php
        // read from measurements in reverse order (DESC) and only reads for one measurepoint
        $result = $conn->query("SELECT * from measurements ORDER BY dateTime DESC LIMIT 1");

        while($row = $result->fetch_assoc()){
        echo 'Timestamp: ' . '<b>' .$row['dateTime'] . '</b>' . '<br><br>' .
         'Temperatur: ' . '<b>' . $row['temp'] . ' C°' . '</b>' . '<br>' .
         'Vandniveau: ' . '<b>' . $row['waterLevel'] . ' cm' . '</b>' . '<br>' .
         'Saltkoncentration: ' . '<b>' . $row['salt'] . ' PSU' . '</b>' . '<br>' .
         'pH: ' . '<b>' . $row['pH'] . '</b>';
        }
?>

    </div>
    </div>

<!-- ********* Measurement chart ********** -->
<div class="container">
   <h2 align="center">Måleoversigt for de sidste 24 timer</h2>
   <br /><br />
   <div id="chart"></div>
  </div>
    </div>
</body>
</html>

<script>
Morris.Line({
 element : 'chart',
 data:[<?php echo $chart_data; ?>],
 xkey:'dateTime',
 ykeys:['temp', 'waterLevel', 'salt', 'pH'],
 labels:['Temperatur', 'Vandniveau', 'Salt', 'pH'],
 hideHover:'auto',
 stacked:true
});
</script>
<!-- ********* end of chart **********  -->
<?php
$conn->close();
?>