import React from 'react';
import {render ,screen } from '@testing-library/react';
import Button from './index';
test('renders button with title',()=>{
    render(<Button background={'red'} callback={jest.fn} title={'Toggle'} />);
    const btnElement=screen.getByText(/Toggle/i);
    expect(btnElement).toBeInTheDocument();
});