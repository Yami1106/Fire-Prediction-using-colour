<?php
// Database connection parameters
$hostname = "localhost";  // Keep it as 'localhost' when using XAMPP
$username = "root";  // Default MySQL user for XAMPP
$password = "";  // Your MySQL password
$database = "minor_project";  // Name of your database

// Create a connection to the MySQL database
$conn = new mysqli($hostname, $username, $password, $database);

// Check if the connection was successful
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}
echo "Database connection is OK<br/>";

// Display the raw POST data for debugging
echo "Raw POST data:<br/>";
print_r($_POST);

// Check if all POST data is set and valid
if (isset($_POST["temperature"], $_POST["humidity"], $_POST["mq2_value"], $_POST["fire_percent"], $_POST["no_fire_percent"])) {
    // Sanitize and assign POST data
    $t = (float) $_POST["temperature"];  // Cast to float to ensure proper type
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
