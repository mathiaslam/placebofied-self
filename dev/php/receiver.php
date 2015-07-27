<?php
$var = $_GET['placebo'];

$fileContent = "Placebo number: ".$var." \n";

//$fileStatus = file_put_contents('myFile.txt',$fileContent, FILE_APPEND);
$fileStatus = file_put_contents('myFile.txt',$fileContent);
if ($fileStatus != false) {
  echo "SUCCESS: data written to file";
} else {
  echo "FAIL: could not write to file";
}
?>
