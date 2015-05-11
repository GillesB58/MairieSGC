<?php

/**
 * Settings form callback.
 * @ingroup forms 
 */
function imagefield_dewslider_admin_settings() {
  $form = array();

  $form['info'] = array(
    '#value' => t('You can manage the behaviour of dewslider for each imagefield field.'),
  );
  
  $options = variable_get('imagefield_dewslider_options',array());
  
  $imagecache_options=array();
  foreach (imagecache_presets() as $preset) {
    $imagecache_options[$preset['presetname']]=$preset['presetname'];
  }
  
  $form['options'] = array(
    '#tree' => TRUE,
  );
  
  foreach(content_fields() as $field => $field_info) {
    if ($field_info['type'] == 'filefield') {
      foreach (array('full', 'teaser') as $format) {
        $options = imagefield_dewslider_get_options($field, $format=='teaser');
        $form['options'][$field][$format] = array(
          '#type' => 'fieldset',
          '#title' => t('Dewslider settings for !field (!format)', array('!field' => $field, '!format' => $format)), 
          '#collapsible' => TRUE,
          '#collapsed' => TRUE,
        );
        $form['options'][$field][$format]['imagecache'] = array(
          '#type' => 'select',
          '#title' => t('Imagecache preset'),
          '#options' => $imagecache_options,
          '#default_value' => $options['imagecache'],
        );        
        $form['options'][$field][$format]['width'] = array(
          '#type' => 'textfield',
          '#title' => t('Width'),
          '#size' => 5,
          '#default_value' => $options['width'],
        );
        $form['options'][$field][$format]['height'] = array(
          '#type' => 'textfield',
          '#title' => t('Height'),
          '#size' => 5,
          '#default_value' => $options['height'],
        );
        
        $form['options'][$field][$format]['showbuttons'] = array(
          '#type' => 'select',
          '#title' => t('Show buttons'),
          '#options' => array('yes' => t('Yes'), 'no' => t('No')),
          '#default_value' => $options['showbuttons'],
        );
        
        $form['options'][$field][$format]['showtitles'] = array(
          '#type' => 'select',
          '#title' => t('Show titles'),
          '#options' => array('yes' => t('Yes'), 'no' => t('No')),
          '#default_value' => $options['showtitles'],
        );
        
        $form['options'][$field][$format]['trimtitles'] = array(
          '#type' => 'textfield',
          '#title' => t('Right trim titles'),
          '#size' => 5,
          '#default_value' => $options['trimtitles'],
          '#description' => t('Right trim titles to N characters. Zero (0) means no trim at all (default).'),
        );
        
        $form['options'][$field][$format]['randomstart'] = array(
          '#type' => 'select',
          '#title' => t('Random start'),
          '#options' => array('yes' => t('Yes'), 'no' => t('No')),
          '#default_value' => $options['randomstart'],
        );
        
        $form['options'][$field][$format]['timer'] = array(
          '#type' => 'textfield',
          '#title' => t('Timer'),
          '#size' => 5,
          '#default_value' => $options['timer'],
        );
        
        $form['options'][$field][$format]['alignbuttons'] = array(
          '#type' => 'select',
          '#title' => t('Align buttons'),
          '#options' => array('top' => t('Top'), 'bottom' => t('Bottom')),
          '#default_value' => $options['alignbuttons'],
        );
        
        $form['options'][$field][$format]['aligntitles'] = array(
          '#type' => 'select',
          '#title' => t('Align titles'),
          '#options' => array('top' => t('Top'), 'bottom' => t('Bottom')),
          '#default_value' => $options['aligntitles'],
        );
        
        $form['options'][$field][$format]['transition'] = array(
          '#type' => 'select',
          '#title' => t('Transition'),
          '#options' => array(
          	'fade' => t('Fade'), 
          	'slide' => t('Slide'), 
          	'push' => t('Push'), 
          	'pop' => t('Pop'), 
          	'warp' => t('Warp'), 
          	'blur' => t('Blur'),
          ),
          '#default_value' => $options['transition'],
        );
        
        $form['options'][$field][$format]['speed'] = array(
          '#type' => 'textfield',
          '#title' => t('Speed'),
          '#size' => 5,
          '#default_value' => $options['speed'],
        );
        
      }
    }
  }
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );  
  
  return $form;
}

/**
 * Submit handler for settings form.
 *
 * @see imagefield_dewslider_admin_settings()
 */
function imagefield_dewslider_admin_settings_submit($form, &$form_state) {
  
  variable_set('imagefield_dewslider_options', $form_state['values']['options']);
  
  drupal_set_message(t('Settings saved'));
}