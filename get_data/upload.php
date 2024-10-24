<?php
// Database connection parameters
$hostname = "localhost";
$username = "root";
$password = "";
$database = "minor_project";

// Create a connection
$conn = new mysqli($hostname, $username, $password, $database);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Query to get data from the table
$sql = "SELECT * FROM sensor_data";
$result = $conn->query($sql);
$conn->close();
?>

<!DOCTYPE html>
<html>

<head>
    <meta charset="UTF-8">
    <title>Fire Prediction Data</title>
    <style>
        table {
            margin: 0 auto;
            font-size: large;
            border: 1px solid black;
        }

        h1 {
            text-align: center;
            color: #006600;
            font-size: xx-large;
            font-family: 'Gill Sans', 'Gill Sans MT',
            ' Calibri', 'Trebuchet MS', 'sans-serif';
        }

        td {
            background-color: #E4F5D4;
            border: 1px solid black;
        }

        th,
        td {
            font-weight: bold;
            border: 1px solid black;
            padding: 10px;
            text-align: center;
        }

        td {
            font-weight: lighter;
        }
    </style>
</head>

<body>
    <section>
        <h1>Fire Prediction</h1>
        <table>
            <tr>
                <th>Temperature</th>
                <th>Humidity</th>
                <th>MQ2 Value</th>
                <th>Fire Percent</th>
                <th>No fire Percent</th>
            <tr>
            <?php
                while($rows=$result->fetch_assoc())
                {
            ?>
            <tr>
            <td><?php echo $rows['temperature'];?></td>
            <td><?php echo $rows['humidity'];?></td>
            <td><?php echo $rows['mq2_value'];?></td>
            <td><?php echo $rows['fire_percent'];?></td>
            <td><?php echo $rows['no_fire_percent'];?></td>   
            </tr>
            <?php
                }
            ?>
        </table>
    </section>
</body>
</html>



