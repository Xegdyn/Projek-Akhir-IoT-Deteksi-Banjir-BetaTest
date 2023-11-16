<?php
$servername = "localhost";
$dbname = "db_iot";
$username = "root";
$password = "";

$api_key_value = "123456789";
$api_key = $sensor = $ketinggian = $status = "";
if ($_SERVER["REQUEST_METHOD"] == "GET") {
  $api_key = test_input($_GET["api_key"]);
  if ($api_key == $api_key_value) {
    $sensor = test_input($_GET["sensor"]);
    $ketinggianSensor = test_input($_GET["ketinggian"]);
    $status = test_input($_GET["status"]);
    $keterangan = ($status) ? "Tidak Hujan" : "Hujan";
    $ketinggianAir = ($ketinggianSensor / 1023) * 200;

    $conn = new mysqli($servername, $username, $password, $dbname);         // Check connection         
    if ($conn->connect_error) {
      die("Koneksi Gagal: " . $conn->connect_error);
    }
    $sql = "INSERT INTO water_level (sensor, ketinggian_air, status_hujan, keterangan_hujan)         
            VALUES ('" . $sensor . "', '" . $ketinggian . "', '" . $status . "', '" . $keterangan . "')";
    if ($conn->query($sql) === TRUE) {
      echo "Record baru berhasil dibuat ";
    } else {
      echo "Error: " . $sql . "<br>" . $conn->error;
    }
    $conn->close();
  } else {
    echo "Verifikasi API Key gagal.";
  }
} else {
  echo "Tidak ada data dikirim melalui HTTP GET.";
}
function test_input($data)
{
  $data = trim($data);
  $data = stripslashes($data);
  $data = htmlspecialchars($data);
  return $data;
}
