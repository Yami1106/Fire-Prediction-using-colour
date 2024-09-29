<?php
// Database connection parameters
$hostname = "localhost";
$username = "root";
$password = "Ashish1106#";
$database = "minor_project";

// Create a connection
$conn = new mysqli($hostname, $username, $password, $database);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}
echo "Database connection is OK<br/>";

// Check if all POST data is set and valid
if (isset($_POST["temperature"], $_POST["humidity"], $_POST["mq2_value"], $_POST["fire_percent"], $_POST["no_fire_percent"])) {
    // Sanitize and assign POST data
    $t = (float) $_POST["temperature"]; // Cast to float to ensure proper type
    $h = (float) $_POST["humidity"];
    $m = (float) $_POST["mq2_value"];
    $f = (float) $_POST["fire_percent"];
    $nf = (float) $_POST["no_fire_percent"];

    // Prepare and bind the SQL statement to avoid SQL injection
    $stmt = $conn->prepare("INSERT INTO sensor_data (temperature, humidity, mq2_value, fire_percent, no_fire_percent) VALUES (?, ?, ?, ?, ?)");
    if ($stmt) {
        $stmt->bind_param("ddddd", $t, $h, $m, $f, $nf);

        // Execute the statement
        if ($stmt->execute()) {
            echo "New record created successfully";
        } else {
            echo "Error: " . $stmt->error;
        }

        // Close the statement
        $stmt->close();
    } else {
        echo "Error preparing statement: " . $conn->error;
    }
} else {
    echo "Required POST data missing.";
}

// Close the database connection
$conn->close();
?>
