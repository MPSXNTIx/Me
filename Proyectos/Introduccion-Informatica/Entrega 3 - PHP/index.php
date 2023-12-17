<!--Trabajo realizado por Anais Muñoz Byron Oñate Manuel Ponce Antonio Quilodran Jorge Salazar-->
<!--Profesor Diego Monsalves-->
<?php 

	$conexion=mysqli_connect('localhost','root','','proyecto');

 ?>

<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <title>Kit Invernadero</title>
    <link type="text/css" rel="stylesheet" href="style.css">
  </head>
  <body>
    <h3>
      <nav>
        <a href="#" id="seccion1-enlace" onclick="mostrarSeccion('seccion1')">Inicio</a>
        <a href="#" id="seccion2-enlace" onclick="mostrarSeccion('seccion2')">Mediciones de Humedad</a>
        <a href="#" id="seccion3-enlace" onclick="mostrarSeccion('seccion3')">Eventos Detectados</a>
        <a href="#" id="seccion4-enlace" onclick="mostrarSeccion('seccion4')">Mediciones de Luminosidad</a>
        <a href="#" id="seccion5-enlace" onclick="mostrarSeccion('seccion5')">Consultas</a>
      </nav>
    </h3>
    <section id="seccion1">
      <div class="clock">
        <div class="time">
          <span id="hours"></span> :
          <span id="minutes"></span> :
          <span id="seconds"></span>
        </div>
      </div>
      <div class="text">
        <h3>
          Descripcion del Proyecto
          <p>El proyecto consiste en desarrollar un prototipo funcional de una solución basada en IoT que permita reducir
            las mermas en los invernaderos que cultivan flores en la región, tanto para exportación como para consumo
            nacional. El mercado mundial de flores se ha vuelto muy competitivo, lo que obliga a los invernaderos locales
            a buscar soluciones para reducir sus costos y aumentar su eficiencia.<br>En definitiva, el proyecto busca
            ofrecer una solución innovadora y tecnológica que permita reducir las mermas en los invernaderos de flores,
            mejorar la eficiencia y competitividad de los productores locales en el mercado mundial de flores.</p>
        </h3>
      </div>
      <div class="container">
        <div class="box">
          <h3>
            Niveles de Humedad
            <p>A la fecha se han realizado 7 mediciones.<br>La medición de humedad más alta registrada es 5%.<br>La
              medición de humedad más baja registrada es 2%.<br>La medición de humedad promedio es 3.7.</p>
          </h3>
        </div>
        <div class="box">
          <h3>
            Historial de actividad
            <p>A la fecha se han detectado 10 eventos.<br>Se han detectado 3 eventos de activación de riego sequedad del
              suelo.<br>Se han detectado 5 eventos de activación de toldo protector por proximidad por aves.<br>Se han
              detectado 2 eventos de activación de toldo protector por bajos niveles de luz (noche).</p>
          </h3>
        </div>
      </div>
    </section>
    <section id="seccion2">
      <div class="container">
        <h3>
          Niveles de Humedad
          <p>A la fecha se han realizado 7 mediciones.<br>La medición de humedad más alta registrada es
            5%.<br>La medición de humedad más baja registrada es 2%.<br>La medición de humedad promedio es 3.7.
          </p>
        </h3>
        <h3>
        <div class="form">
          <br>

        <table border="1" >
          <tr>
            <td>Fecha</td>
            <td>Hora</td>
            <td>Humedad</td>
          </tr>

          <?php 
          $sql="SELECT fecha, hora, CONCAT(humedad_suelo , '%' ) AS porcentaje from humedad";
          $result=mysqli_query($conexion,$sql);

          while($mostrar=mysqli_fetch_array($result)){
          ?>

          <tr>
            <td><?php echo $mostrar['fecha'] ?></td>
            <td><?php echo $mostrar['hora'] ?></td>
            <td><?php echo $mostrar['porcentaje'] ?></td>
          </tr>
        <?php 
        }
        ?>
        </table>
        </div>
        </h3>
      </div>
    </section>
    <section id="seccion3">
      <div class="container">
        <h3>
          Eventos
          <p>A la fecha se han detectado 5 eventos de proximidad.</p>
        </h3>
        <h3>
        <div class="form">
          <br>

          <table border="1" >
          <tr>
            <td>Fecha</td>
            <td>Hora</td>
            <td>distancia</td>
          </tr>

          <?php 
          $sql="SELECT fecha, hora, CONCAT(distancia , 'mts' ) AS metros from evento";
          $result=mysqli_query($conexion,$sql);

          while($mostrar=mysqli_fetch_array($result)){
          ?>

          <tr>
            <td><?php echo $mostrar['fecha'] ?></td>
            <td><?php echo $mostrar['hora'] ?></td>
            <td><?php echo $mostrar['metros'] ?></td>
          </tr>
        <?php 
        }
        ?>
        </table>
        </div>
        </h3>
      </div>
    </section>
    <section id="seccion4">
      <div class="container">
        <h3>
        <div class="form">
          <br>

          <table border="1" >
          <tr>
            <td>Fecha</td>
            <td>Hora de apertura</td>
            <td>Hora de cierre</td>
          </tr>

          <?php 
          $sql="SELECT a.fecha, a.hora, CONCAT(c.hora) AS hora2 from luz_apertura a, luz_cierre c WHERE a.fecha = c.fecha and a.id = c.id";
          $result=mysqli_query($conexion,$sql);

          while($mostrar=mysqli_fetch_array($result)){
          ?>

          <tr>
            <td><?php echo $mostrar['fecha'] ?></td>
            <td><?php echo $mostrar['hora'] ?></td>
            <td><?php echo $mostrar['hora2'] ?></td>
          </tr>
        <?php 
        }
        ?>
        </table>
        </div>
        </h3>
      </div>
    </section>
    <section id="seccion5">
    <form action="registrar.php" method="post">
      <h2>Formulario de consultas</h2>
      <form id="query-form">
        <div>
          <label for="name">Nombre:</label>
          <input type="text" id="name" name="name" required>
        </div>
        <div>
          <label for="email">Correo electrónico:</label>
          <input type="email" id="email" name="email" required>
        </div>
        <div>
          <label for="message">Mensaje:</label>
          <textarea id="message" name="message" required></textarea>
        </div>
        <button type="submit">Enviar</button>
      
      <div id="query-response"></div>
    </section>
    <script src="script.js"></script>
    </form>
  </body>
</html>
