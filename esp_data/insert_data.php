<?php
// // Connect to the database
// $servername = "localhost";
// $username = "root"; // Default WAMP username
// $password = ""; // Default WAMP password
// $dbname = "minor_project"; // Replace with your actual database name

// // Create connection
// $conn = new mysqli($servername, $username, $password, $dbname);

// // Check connection
// if ($conn->connect_error) {
//     die("Connection failed: " . $conn->connect_error);
// }

// // Get data from the HTTP POST request
// $temperature = $_POST['temperature'];
// $humidity = $_POST['humidity'];
// $mq2_value = $_POST['mq2_value'];
// $fire_percent = $_POST['fire_percent'];
// $no_fire_percent = $_POST['no_fire_percent'];

// // Prepare and bind
// $stmt = $conn->prepare("INSERT INTO sensor_data (temperature, humidity, mq2_value, fire_percent, no_fire_percent) VALUES (?, ?, ?, ?, ?)");
// $stmt->bind_param("ddddd", $temperature, $humidity, $mq2_value, $fire_percent, $no_fire_percent);

// // Execute the prepared statement
// if ($stmt->execute()) {
//     echo "New record created successfully";
// } else {
//     echo "Error: " . $stmt->error;
// }

// // Close connection
// $stmt->close();
// $conn->close();

$hostname="localhost";
$username="root";
$password="";
$database="minor_project";

$conn=mysqli_connect($hostname,$username,$password,$database);

if (!$conn){
    die("Connection Failed:".mysqli_connect_error());
}
echo "database connection is ok<br/>";

if (isset($_POST["temperature"]) && isset($_POST["humidity"]) && isset($_POST["mq2_value"]) && isset($_POST["fire_percent"]) && isset($_POST["no_fire_percent"])){
    $t=$_POST["temperature"];
    $h=$_POST["humidity"];
    $m=$_POST["mq2_value"];
    $f=$_POST["fire_percent"];
    $nf=$_POST["no_fire_percent"];
}


$sql="INSERT INTO sensor_data (temperature,humidity,mq2_value,fire_percent,no_fire_percent)  VALUES(?,?,?,?,?)";

if (mysqli_query($conn,$sql)){
    echo "new record created";
} else{
    echo "error".$sql."<hr>".mysqli_error($conn);
}


?>
