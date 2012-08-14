function initDb(db)
{
    window.sys.log("init db");
    db.sql("create table settings (" +
           "id integer not null primary key," +
           "name varchar(30) not null unique," +
           "value varchar(30) not null" +
           ");");

    db.sql("create table messages (" +
           "id integer not null primary key," +
           "ts datetime not null," +
           "user varchar(30) not null," +
           "message varchar(30) not null" +
           ");");
    
    db.sql("create table accounts (" +
           "id integer not null primary key," +
           "type varchar(30) not null," +
           "username varchar(30) not null," +
           "password varchar(30) not null" +
           ");");
    
}

function onLogin()
{
    $("#error").css("display", "none");
    
    var username = $("#login_username").val();
    var password = $("#login_password").val();

    $("#login_username").val("");
    $("#login_password").val("");
    
    var db = window.app.db();
    var result = db.open(username + ".db", password);
    if (result)
    {
        window.sys.log("login success!");
        var path = window.location.href.replace("login.html", "");
        window.sys.log(path + "index.html");
        window.ui.createWindow(path + "index.html");
        window.ui.close();
    }
    else
    {
        $("#error").text("Username or password is incorrect");
        $("#error").css("display", "inline");
    }
    
    return false;
}

function onRegister()
{
    var username = $("#reg_username").val();
    var password1 = $("#reg_password1").val();
    var password2 = $("#reg_password2").val();
    
    $("#reg_username").val("");
    $("#reg_password1").val("");
    $("#reg_password2").val("");
    
    var db = window.app.db();
    if (db.exists(username + ".db"))
    {
        $("#error").text("User already exists");
        $("#error").css("display", "inline");
        return false;
    }
    
    if (password1 != password2)
    {
        $("#error").text("Passwords do not match");
        $("#error").css("display", "inline");
        return false;
    }
    
    window.sys.log("creating db: " + username + ".db");

    db.open(username + ".db", password1);
    initDb(db);
    db.close();
    
    window.sys.log("done");

    $("#login_tab").click();
    
    return false;
}


$(function () {
  // create tabs
  $("ul.tabs").tabs("div.panes > div", {effect: 'fade'});

  if (!window.ui)
    return;
  
  var width = 400;
  var height = 500;
  
  // when tabs are clicked
  $("ul.tabs > li > a").click(function() { 
      $(".error").css("display", "none");
      if ($(this).text() == "Register")
      {
          window.ui.setSize(width, height + 70);
          $("#reg_username").focus();
      }
      else
      {
          window.ui.setSize(width, height);
          $("#login_username").focus();
      }
  });
  
  window.ui.setSize(width, height);
  
  // center window
  centerWindow(width, height);
  
  // bind toolbar
  bindTitleBar();
  
  // bind login and regiter button
  $("#login_submit").click(onLogin);
  $("#register_submit").click(onRegister);

  // focus on username
  $("#login_username").focus();
  
  window.ui.show(true);
});