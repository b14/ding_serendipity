<?php
/**
 * @file
 * This file contains admin forms and functionality related to the ding_serendipity admin interface.
 * @todo comments below
 */

/**
 * Get system settings form with serendipity specific settings.
 */
function ding_serendipity_admin_form($form, &$form_state) {
  $form['ding_serendipity_enable_cache'] = array(
    '#type' => 'checkbox', 
    '#title' => t('Enable cache'), 
    '#description' => t('Allow the serendipity functionality to cache results to boost performance.'),
    '#default_value' => variable_get('ding_serendipity_enable_cache', 0), 
  );
  $form['ding_serendipity_cache_lifetime'] = array(
    '#type' => 'textfield', 
    '#title' => t('Cache lifetime'), 
    '#description' => t('Enter the amount of miliseconds you want the serendipity cache to last.'),
    '#default_value' => variable_get('ding_serendipity_cache_lifetime', 600), 
  );
  $form['ding_serendipity_isslow_timeout'] = array(
    '#type' => 'textfield', 
    '#title' => t('Is slow limit'), 
    '#description' => t('Enter the amount of microseconds you want the serendipity functionality to be limited to.'),
    '#default_value' => variable_get('ding_serendipity_isslow_timeout', 10), 
  );
  
  return system_settings_form($form);
}

/**
 * Get an overview of the current registered serendipity functions and keys.
 */
function ding_serendipity_admin_overview($form, &$form_state) {
  $info = ding_serendipity_get_info();
  
  $form['calls'] = array(
    '#type' => 'tableselect',
    '#header' => array(
      'title' => t('Title'),
      'module' => t('Module'),
      'function' => t('Function'),
      'keys' => t('Context Keys'),
    ),
    '#options' => array()
  );

  foreach ($info as $key => $value) {
    $form['calls']['#options'][$key] = array(
      'title' => $value['title'] . '<div class="description">' . $value['description'] . '</div>',
      'module' => $value['module'],
      'function' => $value['callback'] . '()',
      'keys' => implode(', ', $value['keys']),
    );
  }
  
  $form['context'] = array(
    '#type' => 'fieldset',
    '#title' => t('keys'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  foreach ($info as $key => $value) {
    foreach ($value['keys'] as $context) {
      if (empty($form['context'][$context])) {
        $form['context'][$context] = array(
          '#type' => 'checkbox',
          '#title' => check_plain($context),
          '#default_value' => (!empty($form_state[$context])) ? $form_state[$context] : 0,
        );
      }
    }
  }
  
  return $form;
}