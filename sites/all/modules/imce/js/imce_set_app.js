// $Id: imce_set_app.js,v 1.3.2.3 2008/07/13 11:23:51 ufku Exp $
//When imce url contains &app=appName|fileProperty1@correspondingFieldId1|fileProperty2@correspondingFieldId2|...
//the specified fields are filled with the specified properties of the selected file.

var appFields = {};

//execute when imce loads.
imce.hooks.load.push(function(win) {
  var data = decodeURIComponent(location.href.substr(location.href.lastIndexOf('app=')+4)).split('|');
  var appname = data.shift();
  for (var i in data) {
    var arr = data[i].split('@');
    appFields[arr[0]] = arr[1];
  }
  //set send to
  imce.setSendTo(Drupal.t('Send to @app', {'@app': appname}), appFinish);
  //highlight file
  if (appFields['url']) {
    var filename = $('#'+ appFields['url'], (top.appiFrm||win).opener.document).val();
    imce.highlight(filename.substr(filename.lastIndexOf('/')+1));
  }
});

//sendTo function
var appFinish = function(file, win) {
  var win = top.appiFrm||win, doc = $(win.opener.document);
  for (var i in appFields) {
    doc.find('#'+ appFields[i]).val(file[i]);
  }
  if (appFields['url']) {
    try{doc.find('#'+ appFields['url']).blur().change().focus()}catch(e){};
    try{doc.find('#'+ appFields['url']).trigger('onblur').trigger('onchange').trigger('onfocus')}catch(e){};//inline events
  }
  win.opener.focus();
  win.close();
};
