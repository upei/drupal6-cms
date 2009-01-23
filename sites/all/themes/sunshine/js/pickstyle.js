function pickstyle(whichstyle) {
  var expireDate = new Date()
  var expstring=expireDate.setDate(expireDate.getDate()+30)

  document.cookie = "sunshinestyle=" + whichstyle + "; expires="+expireDate.toGMTString()
}



