<!DOCTYPE html>

<html>
<head>
  <meta charset="UTF-8">
  <title>Insert title here</title>
  <link rel="stylesheet" href="styles.css" />
  <style>
    form {
      margin-left: auto;
      margin-right: auto;
      width: 400px;
    }
  </style>
</head>
<body>
<form action="LoginController" method="post">
  Enter your name: <input type="text" name="name" required> <br/><br/>
  Enter the date: <input type="date" name="date" required> <br/><br/>
  Enter the city: <input type="text" name="city" required> <br/><br/>
  <input type="submit" value="Begin reservation"/>
</form>
</body>
</html>