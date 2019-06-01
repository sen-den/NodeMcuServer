const char MAIN_page[] = R"=====(
<!DOCTYPE html>
<html>
<head>
	<title>ESP8266</title>
</head>
<body>
	<div id="demo">
		<h1>The ESP8266 NodeMCU</h1><BR>

		<div class="slidecontainer">
			<input type="range" id="Servo1" min="0" max="180" value="90" class="slider">
			<input type="range" id="Servo2" min="0" max="180" value="90" class="slider">
		</div>

		<input type="checkbox" id="LED1" name="led[]" value="1">Node LED<br>
		<input type="checkbox" id="LED2" name="led[]" value="2">ESP LED<br>

		<input type="button" onclick="update()" value="Update">

	</div>

	<style>
	.slidecontainer {
		width: 100%; /* Width of the outside container */
	}

	/* The slider itself */
	.slider {
		width: 100%; /* Full-width */
		height: 25px; /* Specified height */
		background: #d3d3d3; /* Grey background */
	}
</style>

<script>
	var list = ["Servo1", "Servo2", "LED1", "LED2"];

	function update() {
		var xhttp = new XMLHttpRequest();
		xhttp.onreadystatechange = function() {
			if (this.readyState == 4 && this.status == 200) {;}
		};

		let values = {};
		list.forEach(function(key) {
			var element = document.getElementById(key);
			var type = element.type;
			var value = element.value;
			var checked = element.checked;

			values[key] = {"type": type, "value": value, "checked": checked};
		});		
		console.log(JSON.stringify(values));

		xhttp.open("POST", '/update', true);
		xhttp.send("values="+JSON.stringify(values));
	}

</script>

</body>
</html>
)=====";
