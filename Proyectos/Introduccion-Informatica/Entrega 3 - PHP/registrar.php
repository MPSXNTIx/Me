<?php

$nombre=$_POST['name'];
$correo=$_POST['email'];
$mensaje=$_POST['message'];
$conexion=mysqli_connect("localhost","root","","proyecto");

$consulta= "insert into consultas (nombre,email,mensaje) values('$nombre','$correo','$mensaje')";

$resultado= mysqli_query($conexion,$consulta);
if($resultado){
    header("Location: index.php");
    exit();
}

mysqli_close($conexion);