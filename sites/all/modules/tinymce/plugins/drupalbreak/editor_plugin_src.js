/**
 * $RCSfile: editor_plugin_src.js,v $
 * $Revision: 1.3 $
 * $Date: 2006/03/27 17:41:43 $
 *
 * @author Nathan Haug
 *
 */

/* Import plugin specific language pack */
tinyMCE.importPluginLanguagePack('drupalbreak', 'en');

var TinyMCE_drupalbreakPlugin = {
  getInfo : function() {
  	return {
  		longname : 'Drupal Teaser/Body Break',
  		author : 'Nathan Haug',
  		authorurl : 'http://www.quicksketch.org',
  		infourl : '',
  		version : '$Revision: 1.3 $'
  	};
  },

  initInstance : function(inst) {
  	tinyMCE.importCSS(inst.getDoc(), tinyMCE.baseURL + "/plugins/drupalbreak/drupalbreak.css");
  },

  getControlHTML : function (control_name) {
    switch (control_name) {
      case "drupalbreak":
        return tinyMCE.getButtonHTML(control_name, 'lang_drupalbreak_desc', '{$pluginurl}/images/drupalbreak.gif', 'mcedrupalbreak', false, 'null');
      case "drupalpagebreak":
        var cmd = 'tinyMCE.execInstanceCommand(\'{$editor_id}\',\'mcedrupalpagebreak\',true);return false;';
        return '<a href="javascript:' + cmd + '" onclick="' + cmd + '" target="_self" onmousedown="return false;"><img id="{$editor_id}_drupalpagebreak" src="{$pluginurl}/images/drupalpagebreak.gif" title="{$lang_drupalpagebreak_desc}" width="20" height="20" class="mceButtonNormal" onmouseover="tinyMCE.switchClass(this,\'mceButtonOver\');" onmouseout="tinyMCE.restoreClass(this);" onmousedown="tinyMCE.restoreAndSwitchClass(this,\'mceButtonDown\');" /></a>';
    }

    return "";
  },


  execCommand : function(editor_id, element, command, user_interface, value) {
  	function getAttrib(elm, name) {
  		return elm.getAttribute(name) ? elm.getAttribute(name) : "";
  	}

      // Handle commands
      switch (command) {
  			case "mcedrupalbreak":
  				var classValue = "";
  				var template = new Array();
  				var inst = tinyMCE.getInstanceById(editor_id);
  				var focusElm = inst.getFocusElement();

  				// Is selection a image
  				if (focusElm != null && focusElm.nodeName.toLowerCase() == "img") {
  					classValue = getAttrib(focusElm, 'class');

  					if (classValue != 'mce_plugin_drupalbreak_break') // Not a Drupal break placeholder
  						return true;

  					action = "update";
  				}

  				html = ''
  	      	+ '<img src="' + (tinyMCE.getParam("theme_href") + "/images/spacer.gif") + '" '
  					+ ' width="100%" height="12px" '
  					+ 'alt="&lt;--break-&gt;" title="&lt;--break--&gt;" class="mce_plugin_drupalbreak_break" />';

  					tinyMCE.execInstanceCommand(editor_id, 'mceInsertContent', false, html);
  				return true;
  			case "mcedrupalpagebreak":
  				var classValue = "";
  				var template = new Array();
  				var inst = tinyMCE.getInstanceById(editor_id);
  				var focusElm = inst.getFocusElement();

  				// Is selection a image
  				if (focusElm != null && focusElm.nodeName.toLowerCase() == "img") {
  					classValue = getAttrib(focusElm, 'class');

  					if (classValue != 'mce_plugin_drupalbreak_pagebreak') // Not a Drupal pagebreak placeholder
  						return true;

  					action = "update";
  				}

  				html = ''
  	      			+ '<img src="' + (tinyMCE.getParam("theme_href") + "/images/spacer.gif") + '" '
  					+ ' width="100%" height="12px" '
  					+ 'alt="&lt;--pagebreak-&gt;" title="&lt;--pagebreak--&gt;" class="mce_plugin_drupalbreak_pagebreak" />';
  	      tinyMCE.execInstanceCommand(editor_id, 'mceInsertContent', false, html);
   				return true;
     }

     // Pass to next handler in chain
     return false;
  },

  cleanup : function(type, content) {
  	switch (type) {

  		case "insert_to_editor":
  			var startPos = 0;

  			// Parse all <!--break--> tags and replace them with images
  			while ((startPos = content.indexOf('<!--break-->', startPos)) != -1) {
  				// Insert image
  				var contentAfter = content.substring(startPos + 12);
  				content = content.substring(0, startPos);
  	      		content += '<img src="' + (tinyMCE.getParam("theme_href") + "/images/spacer.gif") + '" ';
  				content += ' width="100%" height="12px" ';
  				content += 'alt="&lt;--break-&gt;" title="&lt;--break--&gt;" class="mce_plugin_drupalbreak_break" />';
  				content += contentAfter;

  				startPos++;
  			}
  			var startPos = 0;

  			// Parse all <!--pagebreak--> tags and replace them with images
  			while ((startPos = content.indexOf('<!--pagebreak-->', startPos)) != -1) {
  				// Insert image
  				var contentAfter = content.substring(startPos + 16);
  				content = content.substring(0, startPos);
  	      		content += '<img src="' + (tinyMCE.getParam("theme_href") + "/images/spacer.gif") + '" ';
  				content += ' width="100%" height="12px" ';
  				content += 'alt="&lt;--pagebreak-&gt;" title="&lt;--pagebreak--&gt;" class="mce_plugin_drupalbreak_pagebreak" />';
  				content += contentAfter;

  				startPos++;
  			}
  			break;

  		case "get_from_editor":
  			// Parse all img tags and replace them with <!--break-->
  			var startPos = -1;
  			while ((startPos = content.indexOf('<img', startPos+1)) != -1) {
  				var endPos = content.indexOf('/>', startPos);
  				var attribs = parseAttributes(content.substring(startPos + 4, endPos));

  				if (attribs['class'] == "mce_plugin_drupalbreak_break") {
  					endPos += 2;

  					var embedHTML = '<!--break-->';

  					// Insert embed/object chunk
  					chunkBefore = content.substring(0, startPos);
  					chunkAfter = content.substring(endPos);
  					content = chunkBefore + embedHTML + chunkAfter;
  				}
  				if (attribs['class'] == "mce_plugin_drupalbreak_pagebreak") {
  					endPos += 2;

  					var embedHTML = '<!--pagebreak-->';

  					// Insert embed/object chunk
  					chunkBefore = content.substring(0, startPos);
  					chunkAfter = content.substring(endPos);
  					content = chunkBefore + embedHTML + chunkAfter;
  				}
  			}
  			break;
  	}

  	// Pass through to next handler in chain
  	return content;
  	
  	/* Local function within cleanup() that parses the breakimage in and out */
  	function parseAttributes (attribute_string) {
			var attributeName = "";
			var attributeValue = "";
			var withInName;
			var withInValue;
			var attributes = new Array();
			var whiteSpaceRegExp = new RegExp('^[ \n\r\t]+', 'g');
	
			if (attribute_string == null || attribute_string.length < 2)
				return null;
	
			withInName = withInValue = false;
	
			for (var i=0; i<attribute_string.length; i++) {
				var chr = attribute_string.charAt(i);
	
				if ((chr == '"' || chr == "'") && !withInValue)
					withInValue = true;
				else if ((chr == '"' || chr == "'") && withInValue) {
					withInValue = false;
	
					var pos = attributeName.lastIndexOf(' ');
					if (pos != -1)
						attributeName = attributeName.substring(pos+1);
	
					attributes[attributeName.toLowerCase()] = attributeValue.substring(1).toLowerCase();
	
					attributeName = "";
					attributeValue = "";
				} else if (!whiteSpaceRegExp.test(chr) && !withInName && !withInValue)
					withInName = true;
	
				if (chr == '=' && withInName)
					withInName = false;
	
				if (withInName)
					attributeName += chr;
	
				if (withInValue)
					attributeValue += chr;
			}
	
			return attributes;
		}
  },

  handleNodeChange : function(editor_id, node, undo_index, undo_levels, visual_aid, any_selection) {

  	function getAttrib(elm, name) {
  		return elm.getAttribute(name) ? elm.getAttribute(name) : "";
  	}

  	tinyMCE.switchClass(editor_id + '_drupalbreak_break', 'mceButtonNormal');
  	tinyMCE.switchClass(editor_id + '_drupalbreak_pagebreak', 'mceButtonNormal');

  	if (node == null)
  		return;

  	do {
  		if (node.nodeName.toLowerCase() == "img" && getAttrib(node, 'class').indexOf('mce_plugin_drupalbreak_break') == 0)
  			tinyMCE.switchClass(editor_id + '_drupalbreak_break', 'mceButtonSelected');
  		if (node.nodeName.toLowerCase() == "img" && getAttrib(node, 'class').indexOf('mce_plugin_drupalbreak_pagebreak') == 0)
  			tinyMCE.switchClass(editor_id + '_drupalbreak_pagebreak', 'mceButtonSelected');
  	} while ((node = node.parentNode));

  	return true;
  }
};

tinyMCE.addPlugin("drupalbreak", TinyMCE_drupalbreakPlugin);
