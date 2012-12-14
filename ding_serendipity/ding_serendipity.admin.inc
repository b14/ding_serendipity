<?php
// $id$ 

/**
 * @file
 * This file contains admin forms and functionality related to the ding_serendipity admin interface.
 * @todo comments below
 */

function ding_serendipity_admin_form($form, &$form_state) {
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
  
  // $form['submit'] = array(
    // '#type' => 'submit',
    // '#value' => t('Save')
  // );
  return $form;
}