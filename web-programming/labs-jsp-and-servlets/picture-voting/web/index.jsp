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
  Enter username: <input type="text" name="username" required> <br/><br/>
  Enter password : <input type="password" name="password" required> <br/><br/>
  <input type="submit" value="Login"/>
</form>
</body>
</html>