<?php
include_once 'includes/dbh.inc.php';
?>

<!DOCTYPE html>
<html>
    <head>
        <title>Read Data from DB test</title>
</head>
<body>

<?php
    $sqlCmd = "SELECT * FROM measurements;";
    $result = mysqli_query($conn, $sqlCmd);
    $resultcheck = mysqli_num_rows($result);

    if($resultcheck > 0){
        while($row = mysqli_fetch_assoc($result)){
            echo $row['temp'] . echo $row['waterLevel'] . echo $row['salt'] . echo $row['timeStamp'] . "<br>";
        }
    }
?>

</body>
</html>