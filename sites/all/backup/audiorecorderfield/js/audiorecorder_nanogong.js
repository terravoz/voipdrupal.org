function submitVoice(field_name,delta) { 
	//Remove any error messages
	$("#edit-field-"+field_name+"-"+delta+"-wrapper .error").remove();
	//Disable the button
	$("#nanogong-button-"+field_name+"-"+delta).attr('disabled', 'disabled');	
	
	if($("#nanogong-button-"+field_name+"-"+delta).val()=='Upload'){
	//Upload button
		
		// Find the applet object 
		//var applet = document.getElementById("nanogong-"+delta); 
		var applet = $("#nanogong-"+field_name+"-"+delta).get(0); 
		// Tell the applet to post the voice recording to the backend PHP code 
		var path=Drupal.settings.basePath +"?q=nanogong_file_receive";
		
		var fid = applet.sendGongRequest( "PostToForm", path, "voicefile", "", "temp"); 
		if (fid == null || fid == ""){
		$("#nanogong-button-"+field_name+"-"+delta).removeAttr("disabled");
		$("#edit-field-"+field_name+"-"+delta+"-wrapper").append('<div class="messages error file-upload-js-error">Failed to submit the voice recording!</div>');

		} 
		else{
			$.ajax({
					type: "GET",
					url: Drupal.settings.basePath +"?q=nanogong_preview",
					data: "fid=" + fid+"&field_name=" + field_name+"&delta=" +delta,
					dataType: 'json',
					success: NanogongPreview
				});
			$("#edit-field-"+field_name+"-"+delta+"-fid").val(fid);
		} 
	}
	else{
		//Remove button
		var fid =$("#edit-field-"+field_name+"-"+delta+"-fid").val();
		/*$.ajax({
				type: "GET",
				url: Drupal.settings.basePath +"nanogong_file_remove",
				data: "fid=" + fid+"&field_name=" + field_name+"&delta=" +delta,
				dataType: 'json',
				success: NanogongRemove
		});*/
	$("#edit-field-"+field_name+"-"+delta+"-wrapper .filefield-file-info").remove();
	$("#edit-field-"+field_name+"-"+delta+"-fid").val("");
	$("#nanogong-button-"+field_name+"-"+delta).removeAttr("disabled");
	$("#nanogong-button-"+field_name+"-"+delta).val('Upload');
	//Remove and reload the applet
	//$("#nanogong-"+field_name+"-"+delta).remove();
	$("#nanogong-"+field_name+"-"+delta+"-wrapper").remove();
	$("#nanogong-button-"+field_name+"-"+delta).before('<div class="nanogong-recorder" id="nanogong-'+field_name+'-'+delta+'-wrapper"><applet id="nanogong-'+field_name+'-'+delta+'" archive="'+Drupal.settings.basePath+Drupal.settings.audiorecorderfield_path+'/recorders/nanogong.jar" code="gong.NanoGong" width="113" height="40"><param name="ShowSaveButton" value="false" /><param name="ShowSpeedButton" value="false" /></applet></div>');
		
	}
} 

function NanogongPreview(data){
	//$("#edit-field-"+data.field_name+"-"+data.delta+"-wrapper").append(data.preview);
	//Remove Upload button and add Remove button
	$("#nanogong-button-"+data.field_name+"-"+data.delta).removeAttr("disabled");
	$("#nanogong-button-"+data.field_name+"-"+data.delta).val('Remove');
	$("#nanogong-"+data.field_name+"-"+data.delta+"-wrapper").remove();
	$("#nanogong-button-"+data.field_name+"-"+data.delta).before(data.nanogong);
}

/*
function NanogongRemove(data){
	$("#edit-field-"+data.field_name+"-"+data.delta+"-wrapper .filefield-file-info").remove();
	$("#edit-field-"+data.field_name+"-"+data.delta+"-fid").val("");
	$("#nanogong-button-"+data.delta).removeAttr("disabled");
	$("#nanogong-button-"+data.delta).val('Upload');
	$("#nanogong-"+data.delta).remove();
}
*/